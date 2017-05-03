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

                    # Index into vals in the same position as keyword
                    val = str(valsDefine[keywordsDefine.index(s[1])]) 
                    line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+' \
                                  .format(s[1]),r"\g<1>{0}".format(val),line)
                f2.write(line)     

            if line.startswith("typedef"): # Update typedefs

                s=line.split()
                if s[2] in keywordsTypes: # Grabs the KEYWORD
                    val = valsType             
                    line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+' \
                                  .format(s[0]),r"\g<1>{0}".format(val),line)
                f2.write(line)          

    f1.close()
    f2.close()

    os.remove('c/benchmark.h')
    os.rename('c/benchmark.xh', 'c/benchmark.h')    

# Benchmarking of matrix multiplication, allows for enabling of synthesis

def matmul(synth = 0, hw_test = 0):

    # This string is printed if HwA is correct

    correct_str = "Results correct";

    # These lists holds the definitions for the
    # defines and typedefs to be changed

    keywordsDefine  = ["DIM","NBANKS"]
    keywordsTypes   = ["mat_type;","vec_type;"]    

    # These values define the parameter space to explore for matrix multiplication

    # nbanksList  = [3, 5, 9]
    # dimList     = [4, 16, 32]
    # valsType    = ["float", "int"]
    # appList     = ["hwa_matmul_nb", "hwa_matmul_nb_spm", "hwa_matmul_nb_uncached", 
    #                "tacle_matrix1_spm", "tacle_matrix1_uncached"]

    nbanksList  = [3]
    dimList     = [4]
    valsType    = ["float"]
    appList     = ["hwa_matmul_nb"]                   

    # Measurements will be stored in the dataArray

    dataArray = np.zeros([len(valsType) * len(dimList) * len(nbanksList), len(appList)])

    # Add 1 since it will be horizontally stacked later
    # max string length of 10

    csv_rows = np.zeros([len(valsType) * len(dimList) * len(nbanksList) + 1, 3], dtype = "S10") 

    for i in range(0, len(valsType)):               # Iterate over data type (float/int)
        for j in range(0, len(nbanksList)):         # Iterate over number of banks
            for k in range(0, len(dimList)):        # Iterate over matrix dimensions
                for g in range(0, len(appList)):    # Iterate over apps      

                    # Get the current iteration options      

                    app = appList[g]

                    valsDefine = [dimList[k], nbanksList[j]]

                    # Update the benchmark.h file

                    update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])   

                    # Project name string
                    
                    project = ('matmul_{type}_{nbank}b_{dim}x{dim}') \
                              .format(type = valsType[i], nbank=nbanksList[j], dim=dimList[k])

                    # cmd based on function options

                    if synth == 1:
                        cmd = ('make COM_PORT?=/dev/ttyUSB1 '
                               'HWA_PROJECT={prj} '
                               'APP={app} '
                               'comp hwa_synth hwa_config download') \
                                .format(prj=project, app = app)
                    else:                   
                        cmd = ('make COM_PORT?=/dev/ttyUSB1 '
                               'HWA_PROJECT={prj} '
                               'APP={app} '
                               'comp hwa_config download') \
                                .format(prj=project, app = app)          


                    print("\n*******************************************")
                    print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" \
                          % (valsType[i], nbanksList[j], dimList[k]))
                    print("APP: %s" % (app))                    
                    print("*******************************************\n")                

                    # We now try to do the benchmarking

                    retries = 2          

                    while retries > 0:

                        result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)
                        result = result.stdout.decode('utf-8') # Grab stdout

                        if hw_test:
                            if not correct_str.find(result):
                                print("Error:")
                            else:
                                print("Correct")

                        # Grab everything after "#Cycles ="
                        test_out = (result.partition("#Cycles = ")[2])

                        # Try to see if we got a result

                        try:

                            num_cycles = int(test_out)
                            break

                        except:

                            retries = retries - 1
                            print("Error when getting the number of cycles")
                            print(result)
                            continue

                    if retries > 0:

	                    # Success

	                    print("The number of cycles is: %d" % (num_cycles))

	                    dataArray[k+j*len(nbanksList) + i \
	                               * len(nbanksList) * len(dimList)][g] = num_cycles

	                    # Add {dim}x{dim} (e.g. 4x4)

	                    csv_rows[k + j * len(nbanksList) + i \
	                               * len(nbanksList) * len(dimList) + 1][2] \
	                               = ('{dim}x{dim}').format(dim=dimList[k])   

            # Add NBANKS={nbank} (e.g. NBANKS=5)                                   
            # subtract 1 is for alignment

            csv_rows[k + j * len(nbanksList) + i \
                       * len(nbanksList) * len(dimList) - 1][1] \
                       = ('NBANKS={nbank}').format(nbank = nbanksList[j])

        # Add Type={type} (e.g. Type=int)                                   
        # subtract ? is for alignment                       

        csv_rows[k + j * len(nbanksList) + i \
                   * len(nbanksList) * len(dimList)][0] \
                   = ('Type={type}').format(type = valsType[i])                       

    # Print the dataArray

    print(dataArray)

    # We now vertically stack the appList first and then the dataArray

    dataOut = np.vstack((appList, dataArray))

    # We now horizontally stack the data with csv_rows.

    dataOut = np.hstack((csv_rows, dataOut))

    np.savetxt('test.out', dataOut, delimiter=',', fmt='%s') 


def main(): 

    matmul(synth = 1, hw_test = 0)

if __name__ == "__main__":
    sys.exit(main())    