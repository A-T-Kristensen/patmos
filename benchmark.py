#!/usr/bin/python3

# Run with python3

import re
import os
import sys
import subprocess

# TODO:
# Add function to write benchmarks to file
# Add functions for other HwA

# update updates the header file

def update_header(keywordsDefine, valsDefine, keywordsTypes, valsType):

    with open('c/benchmark.h','r') as f1, open('c/benchmark.xh','w') as f2:
        for line in f1:
            if line.startswith("#define"): # Update defines
                s=line.split()
                if s[1] in keywordsDefine: # Grabs the KEYWORD
                    val = str(valsDefine[keywordsDefine.index(s[1])]) # Index into vals in the same position as keyword
                    line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+'.format(s[1]),r"\g<1>{0}".format(val),line)
                f2.write(line)     

            if line.startswith("typedef"): # Update typedefs
                s=line.split()
                if s[2] in keywordsTypes: # Grabs the KEYWORD
                    val = valsType             
                    line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+'.format(s[0]),r"\g<1>{0}".format(val),line)
                f2.write(line) 	        

    f1.close()
    f2.close()

    os.remove('c/benchmark.h')
    os.rename('c/benchmark.xh', 'c/benchmark.h')    

# Benchmarking of matrix multiplication, allows for enabling of synthesis

def matmul(synth = 0):

    keywordsDefine=["DIM","NBANKS"]
    keywordsTypes = ["mat_type;","vec_type;"]    

    # These values define the parameter space to explore

    NBANKS = [3, 5, 9]
    DIM = [4, 16, 32]
    valsType = ["float", "int"]

    for i in range(0, len(valsType)):       # Iterate over float/int
        for j in range(0, len(NBANKS)):     # Iterate over NBanks
            for k in range(0, len(DIM)):    # Iterate over DIM

                print("\n*******************************************")
                print("\nMatmul: type = %s, NBANKS = %d, DIM = %d\n" % (valsType[i], NBANKS[j], DIM[k]))
                print("*******************************************\n")                

                valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

                # Update the benchmark.h file

                update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])

                app = "hwa_matmul_nb"                

                # Project name string
                project = ('matmul_{type}_{nbank}b_{dim}x{dim}').format(type = valsType[i], nbank=NBANKS[j], dim=DIM[k])

                if synth == 1:
                    cmd = ('make COM_PORT?=/dev/ttyUSB1 '
                		'HWA_PROJECT={prj} '
                		'APP={app} '
                		'comp hwa_synth hwa_config download').format(prj=project, app = app)
                else:                   
                    cmd = ('make COM_PORT?=/dev/ttyUSB1 '
                        'HWA_PROJECT={prj} '
                        'APP={app} '
                        'comp hwa_config download').format(prj=project, app = app)                

                #os.system(cmd)
                result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)	

                print("\nTest result:\n")

                test = result.stdout.decode('utf-8')

                print(test.partition("HWA Running")[2]) # Print everything after HWA Running


def main():	
	matmul(synth = 0)

if __name__ == "__main__":
    sys.exit(main())	