#!/usr/bin/python3

import re
import os
import sys
import subprocess

# Run with python3

# update updates the header file

def update(keywordsDefine, valsDefine, keywordsTypes, valsType):

	# Update defines

	with open('c/benchmark.h','r') as f1, open('c/benchmark.xh','w') as f2:
	    for line in f1:
	        if line.startswith("#define"):
	            s=line.split()
	            if s[1] in keywordsDefine: # Grabs the KEYWORD
	                val = str(valsDefine[keywordsDefine.index(s[1])]) # Index into vals in the same position as keyword
	                line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+'.format(s[1]),r"\g<1>{0}".format(val),line)
	            f2.write(line)     

	        if line.startswith("typedef"):
	            s=line.split()
	            if s[2] in keywordsTypes: # Grabs the KEYWORD
	                val = valsType             
	                line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+'.format(s[0]),r"\g<1>{0}".format(val),line)
	            f2.write(line) 	        

	f1.close()
	f2.close()

def update_test():

    NBANKS = [3, 5, 9]
    DIM = [4, 16, 32]
    valsType = ["float", "int"]
    synth = 0

    keywordsDefine=["DIM","NBANKS"]
    keywordsTypes = ["mat_type;","vec_type;"]

    for i in range(0, len(valsType)): # Iterate over float/int
        for j in range(0, len(NBANKS)): # Iterate over NBanks
            for k in range(0, len(DIM)): # Iterate over DIM

                # Goes to inner for loop
                print("Matmul: type = %s, NBANKS = %d, DIM = %d" % (valsType[i], NBANKS[j], DIM[k]))

                valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

                update(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])

                os.remove('c/benchmark.h')
                os.rename('c/benchmark.xh', 'c/benchmark.h')

                if NBANKS[j] == 3:
                    app = "hwa_matmul_nb"
                elif NBANKS[j] == 5:
                    app = "hwa_matmul_5b"
                else:
                    app = "hwa_matmul_9b"

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

                test = result.stdout.decode('utf-8')

                print(test.partition("HWA Running")[2]) # Print everything after HWA Running

def update_hwa_test():

    NBANKS = [9]
    DIM = [16]
    valsType = ["float"]
    synth = 1

    keywordsDefine=["DIM","NBANKS"]
    keywordsTypes = ["mat_type;","vec_type;"]

    for i in range(0, len(valsType)): # Iterate over float/int
        for j in range(0, len(NBANKS)): # Iterate over NBanks
            for k in range(0, len(DIM)): # Iterate over DIM

                # Goes to inner for loop
                print("Matmul: type = %s, NBANKS = %d, DIM = %d" % (valsType[i], NBANKS[j], DIM[k]))

                valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

                update(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])

                os.remove('c/benchmark.h')
                os.rename('c/benchmark.xh', 'c/benchmark.h')

                if NBANKS[j] == 3:
                    app = "hwa_matmul_nb"
                elif NBANKS[j] == 5:
                    app = "hwa_matmul_5b"
                else:
                    app = "hwa_matmul_9b"

                project = ('matmul_{type}_{nbank}b_{dim}x{dim}').format(type = valsType[i], nbank=NBANKS[j], dim=DIM[k])

                # First synthesize
                cmd = ('make HWA_PROJECT={prj} '
                        'hwa_synth').format(prj=project)

                os.system(cmd)
                
                cmd = ('make COM_PORT?=/dev/ttyUSB1 '
                    'HWA_PROJECT={prj} '
                    'APP={app} '
                    'comp hwa_config download').format(prj=project, app = app)                

                # Test
                result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)  

                test = result.stdout.decode('utf-8')

                print(test.partition("HWA Running")[2]) # Print everything after HWA Running                

def update_hwa():

    NBANKS = [3, 5, 9]
    DIM = [4, 16, 32]
    valsType = ["float", "int"]

    keywordsDefine=["DIM","NBANKS"]
    keywordsTypes = ["mat_type;","vec_type;"]

    for i in range(0, len(valsType)): # Iterate over float/int
        for j in range(0, len(NBANKS)): # Iterate over NBanks
            for k in range(0, len(DIM)): # Iterate over DIM

                # Goes to inner for loop
                valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

                project = ('matmul_{type}_{nbank}b_{dim}x{dim}').format(type = valsType[i], nbank=NBANKS[j], dim=DIM[k])

                cmd = ('make HWA_PROJECT={prj} '
                        'hwa_synth').format(prj=project)

                os.system(cmd)

# def update_hwa_test():

#     NBANKS = [5, 9]
#     DIM = [4, 16, 32]
#     valsType = ["float", "int"]

#     keywordsDefine=["DIM","NBANKS"]
#     keywordsTypes = ["mat_type;","vec_type;"]

#     for i in range(0, len(valsType)): # Iterate over float/int
#         for j in range(0, len(NBANKS)): # Iterate over NBanks
#             for k in range(0, len(DIM)): # Iterate over DIM

#                 # Goes to inner for loop
#                 valsDefine=[DIM[k],NBANKS[j]]    # Make a set of vals depending on test

#                 update(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])

#                 os.remove('c/benchmark.h')
#                 os.rename('c/benchmark.xh', 'c/benchmark.h')

#                 app = "hwa_matmul_nb"
#                 project = ('matmul_{type}_{nbank}b_{dim}x{dim}').format(type = valsType[i], nbank=NBANKS[j], dim=DIM[k])

#                 cmd = ('make COM_PORT?=/dev/ttyUSB1 '
#                         'HWA_PROJECT={prj} '
#                         'APP={app} '
#                         'comp hwa_synth hwa_config download').format(prj=project, app = app)

#                 os.system(cmd)    



def main():	
	update_test()
    #update_hwa_test()

if __name__ == "__main__":
    sys.exit(main())	


