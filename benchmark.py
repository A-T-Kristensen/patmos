#!/usr/bin/python3

# Run with python3

import re
import os
import sys
import subprocess
import numpy as np

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

def matmul(synth = 0, hw_test = 0):

    keywordsDefine=["DIM","NBANKS"]
    keywordsTypes = ["mat_type;","vec_type;"]    

    # These values define the parameter space to explore

    # NBANKS = [3, 5, 9]
    # DIM = [4, 16, 32]
    # valsType = ["float", "int"]
    # APPS = ["hwa_matmul_nb", "hwa_matmul_nb_spm", "hwa_matmul_nb_uncached", "tacle_matrix1", "tacle_matrix1_spm", "tacle_matrix1_uncached"]
    
    NBANKS = [3]
    DIM = [4, 16]
    valsType = ["float"]

    APPS = ["hwa_matmul_nb", "hwa_matmul_nb_spm"]

    data = np.zeros([len(valsType)*len(DIM)*len(NBANKS) ,len(APPS)])

    csv_rows = np.zeros([len(valsType)*len(DIM)*len(NBANKS) + 1, 2], dtype="S10") # Add 1 since it will be horizontally stacked later
                                                                                  # max string length of 10

    for i in range(0, len(valsType)):       # Iterate over float/int
        for j in range(0, len(NBANKS)):     # Iterate over NBanks
            for k in range(0, len(DIM)):    # Iterate over DIM
                for g in range(0, len(APPS)):    # Iterate over apps            

                    app = APPS[g]
                    valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

                    print("\n*******************************************")
                    print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" % (valsType[i], NBANKS[j], DIM[k]))
                    print("APP: %s" % (app))                    
                    print("*******************************************\n")                


                    # Update the benchmark.h file

                    update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])    

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

                    result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)	# Use subprocess to execute cmd in terminal

                    test_out = result.stdout.decode('utf-8') # Grab stdout
                    test_out = (test_out.partition("#Cycles = ")[2]) # Grab everything after "#Cycles ="

                    correct_str = "Results correct";

                    if hw_test:
                        if not correct_str.find(test_out):
                            print("Error:")
                        else:
                            print("Correct")

                    num_cycles = int((test_out.splitlines())[0]) #Get the number of cycles

                    print("The number of cycles is: %d" % (num_cycles))

                    data[k+j*len(NBANKS) + i*len(NBANKS)*len(DIM)][g] = num_cycles

                    csv_rows[k+j*len(NBANKS) + i*len(NBANKS)*len(DIM) + 1][1] = ('{dim}x{dim}').format(dim=DIM[k])

        csv_rows[k+j*len(NBANKS) + i*len(NBANKS)*len(DIM)][0] = ('NBANKS={nbank}').format(nbank = NBANKS[j])


    # Print the data
    print(data)

    out = np.vstack((APPS, data))
    out = np.hstack((csv_rows, out))

    np.savetxt('test.out', out, delimiter=',', fmt='%s') 

def main():	
	matmul(synth = 0, hw_test = 0)

if __name__ == "__main__":
    sys.exit(main())	