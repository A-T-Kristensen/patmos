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

    with open('c/libhwa/benchmark.h','r') as f1, open('c/libhwa/benchmark.xh','w') as f2:

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

    os.remove('c/libhwa/benchmark.h')
    os.rename('c/libhwa/benchmark.xh', 'c/libhwa/benchmark.h')    

# Benchmarking of matrix multiplication, allows for enabling of synthesis

# def matmul(synth = 0, hw_test = 0):

#     # This string is printed if HwA is correct

#     correct_str = "Results correct";

#     # These lists holds the definitions for the
#     # defines and typedefs to be changed

#     keywordsDefine  = ["DIM","NBANKS"]
#     keywordsTypes   = ["mat_type;","vec_type;"]    

#     # These values define the parameter space to explore for matrix multiplication

#     # nbanksList  = [3, 5, 9]
#     # dimList     = [4, 16, 32]
#     # valsType    = ["float", "int"]
#     # appList     = ["hwa_matmul_nb", "hwa_matmul_nb_spm", "hwa_matmul_nb_uncached", 
#     #                "tacle_matrix1_spm", "tacle_matrix1_uncached"]               



#     nbanksList  = [3, 5, 9]
#     dimList     = [4]
#     valsType    = ["float"]
#     appList     = ["hwa_matmul_nb", "tacle_matrix1_uncached"]   

#     # Measurements will be stored in the dataArray

#     computeArray = np.zeros([len(valsType) * len(dimList) * len(nbanksList), len(appList)])
#     transferArray = np.zeros([len(valsType) * len(dimList) * len(nbanksList), len(appList)])    

#     # Add 1 since it will be horizontally stacked later
#     # max string length of 10

#     csv_rows = np.zeros([len(valsType) * len(dimList) * len(nbanksList) + 1, 3], dtype = "S10") 

#     for i in range(0, len(valsType)):               # Iterate over data type (float/int)
#         for j in range(0, len(nbanksList)):         # Iterate over number of banks
#             for k in range(0, len(dimList)):        # Iterate over matrix dimensions
#                 for g in range(0, len(appList)):    # Iterate over apps      

#                     # Get the current iteration options      

#                     app = appList[g]

#                     valsDefine = [dimList[k], nbanksList[j]]

#                     # Update the benchmark.h file

#                     update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])   

#                     # Project name string
                    
#                     project = ('matmul_{type}_{nbank}b_{dim}x{dim}') \
#                               .format(type = valsType[i], nbank=nbanksList[j], dim=dimList[k])

#                     # cmd based on function options

#                     if synth == 1:
#                         cmd = ('make COM_PORT?=/dev/ttyUSB1 '
#                                'HWA_PROJECT={prj} '
#                                'APP={app} '
#                                'comp hwa_synth hwa_config download') \
#                                 .format(prj=project, app = app)
#                     else:                   
#                         cmd = ('make COM_PORT?=/dev/ttyUSB1 '
#                                'HWA_PROJECT={prj} '
#                                'APP={app} '
#                                'comp hwa_config download') \
#                                 .format(prj=project, app = app)          


#                     print("\n*******************************************")
#                     print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" \
#                           % (valsType[i], nbanksList[j], dimList[k]))
#                     print("APP: %s" % (app))                    
#                     print("*******************************************\n")                

#                     # We now try to do the benchmarking

#                     retries = 2          
#                     num_cycles = i

#                     while retries > 0:

#                         result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)
#                         result = result.stdout.decode('utf-8') # Grab stdout

#                         if hw_test:
#                             if not correct_str.find(result):
#                                 print("Error:")
#                             else:
#                                 print("Correct")

#                         # Grab everything after "#Cycles ="
#                         test_out = (result.partition("Benchmarking")[2])

#                         compute_time = re.search('<compute>(.*)</compute>', test_out)
#                         transfer_time =  re.search('<transfer>(.*)</transfer>', test_out)

#                         # Try to see if we got a result

#                         try:

#                             num_cycles = int(compute_time)
#                             break

#                         except:

#                             retries = retries - 1
#                             print("Error when getting the number of cycles")
#                             print(result)
#                             if synth == 0:
#                                 continue
#                             else:
#                                 break

#                     if retries > 0:

# 	                    # Success

# 	                    print("The number of cycles is: %d" % (num_cycles))

# 	                    dataArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = num_cycles


# 	                    # Add {dim}x{dim} (e.g. 4x4)
#                         # add 1 is for alignment                       

# 	                    csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) + 1][2] \
# 	                               = ('{dim}x{dim}').format(dim=dimList[k])   

#             # Add NBANKS={nbank} (e.g. NBANKS=5)                                   
#             # add 2 is for alignment

#             csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) - len(dimList) + 2][1] \
#                        = ('NBANKS={nbank}').format(nbank = nbanksList[j])

#         # Add Type={type} (e.g. Type=int)                                   
#         # add 1 is for alignment                       

#         csv_rows[i * len(nbanksList) * len(dimList) + 1][0] \
#                    = ('Type={type}').format(type = valsType[i])                       

#     # Print the dataArray

#     print(dataArray)

#     # We now vertically stack the appList first and then the dataArray

#     dataOut = np.vstack((appList, dataArray))

#     # We now horizontally stack the data with csv_rows.

#     dataOut = np.hstack((csv_rows, dataOut))

#     np.savetxt('matmul.csv', dataOut, delimiter=',', fmt='%s') 


def run_benchmark(project, app, synth, hw_test):

    # cmd based on function options

    correct_str = "Results correct";    

    if synth == 1:
        cmd = ('make -B COM_PORT?=/dev/ttyUSB1 '
               'HWA_PROJECT={prj} '
               'APP={app} '
               'comp hwa_synth hwa_config download') \
                .format(prj=project, app = app)
    else:                   
        cmd = ('make -B COM_PORT?=/dev/ttyUSB1 '
               'HWA_PROJECT={prj} '
               'APP={app} '
               'comp hwa_config download') \
                .format(prj=project, app = app)          


    # We now try to do the benchmarking

    retries = 2          

    while retries > 0:

        # Redirect stderr to PIPE, hides the warnings when compiling
        result = subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        result = result.stdout.decode('utf-8') 

        if hw_test:
            if not correct_str.find(result):
                print("Error:")
            else:
                print("Correct")

        test_out = (result.partition("Benchmarking")[2])
        print(test_out)
        # Try to see if we got a result

        try:

            compute_time = int((re.search('<compute>(.*)</compute>', test_out)).group(1))
            transfer_time = int((re.search('<transfer>(.*)</transfer>', test_out)).group(1))

            return [compute_time, transfer_time, retries]

        except:

            retries = retries - 1
            print("Error when getting the number of cycles")
            print(result)
            
            if synth == 0:
                continue
            else:
                break

    return [0, 0, retries]

def store_benchmark(bench_name, appList, computeArray, transferArray, totalArray, csv_rows):

    computeOut = np.vstack((appList, computeArray))
    computeOut = np.hstack((csv_rows, computeOut))

    transferOut = np.vstack((appList, transferArray))
    transferOut = np.hstack((csv_rows, transferOut))

    totalOut = np.vstack((appList, totalArray))
    totalOut = np.hstack((csv_rows, totalOut))    

    dataOut = np.vstack((computeOut, transferOut, totalOut))

    np.savetxt(bench_name + '_compute.csv', computeOut, delimiter=',', fmt='%s') 
    np.savetxt(bench_name + '_transfer.csv', transferOut, delimiter=',', fmt='%s') 
    np.savetxt(bench_name + '.csv', dataOut, delimiter=',', fmt='%s') 


def matmul(synth = 0, hw_test = 0):

    # This string is printed if HwA is correct


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
                
    nbanksList  = [5, 9]
    dimList     = [16, 32]
    valsType    = ["float"]
    appList     = ["hwa_matmul_nb_spm"]     

    # Measurements will be stored in the dataArray

    size = int(len(valsType) * len(dimList) * len(nbanksList))
    computeArray = np.zeros([size, len(appList)])
    transferArray = np.zeros([size, len(appList)]) 
    totalArray = np.zeros([size, len(appList)]) 

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

                    print("\n*******************************************")
                    print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" \
                          % (valsType[i], nbanksList[j], dimList[k]))
                    print("APP: %s" % (app))                    
                    print("*******************************************\n")                     

                    # Update the benchmark.h file

                    update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])   

                    # Project name string
                    
                    project = ('matmul_{type}_{nbank}b_{dim}x{dim}') \
                              .format(type = valsType[i], nbank=nbanksList[j], dim=dimList[k])

                    [compute_time, transfer_time, retries] = run_benchmark(project, app, synth, hw_test)

                    if retries > 0:

                        # Success

                        print("The number of cycles for computation is: %d" % (compute_time))
                        print("The number of cycles for transfer is: %d" % (transfer_time))

                        computeArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = compute_time
                        transferArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = transfer_time
                        totalArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = transfer_time + compute_time

                        # Add {dim}x{dim} (e.g. 4x4)
                        # add 1 is for alignment                       

                        csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) + 1][2] \
                                   = ('{dim}x{dim}').format(dim=dimList[k])   

            # Add NBANKS={nbank} (e.g. NBANKS=5)                                   
            # add 2 is for alignment

            csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) - len(dimList) + 2][1] \
                       = ('NBANKS={nbank}').format(nbank = nbanksList[j])

        # Add Type={type} (e.g. Type=int)                                   
        # add 1 is for alignment                       

        csv_rows[i * len(nbanksList) * len(dimList) + 1][0] \
                   = ('Type={type}').format(type = valsType[i])                       

    # We now vertically stack the appList first and then the dataArray

    store_benchmark("matmul", appList, computeArray, transferArray, totalArray, csv_rows)


def minver(synth = 0, hw_test = 0):

    # This string is printed if HwA is correct


    # These lists holds the definitions for the
    # defines and typedefs to be changed

    keywordsDefine  = ["DIM","NBANKS"]
    keywordsTypes   = ["mat_type;","vec_type;"]    

    # These values define the parameter space to explore for matrix multiplication

    # nbanksList  = [1, 2, 4]
    # dimList     = [4, 16, 32]
    # valsType    = ["float"]
    # appList     = ["hwa_minver", "tacle_minver"] 

    nbanksList  = [1, 2, 4]
    dimList     = [4, 16, 32]
    valsType    = ["float"]
    appList     = ["hwa_minver"]                

    # Measurements will be stored in the dataArray

    size = int(len(valsType) * len(dimList) * len(nbanksList))
    computeArray = np.zeros([size, len(appList)])
    transferArray = np.zeros([size, len(appList)]) 
    totalArray = np.zeros([size, len(appList)]) 

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

                    print("\n*******************************************")
                    print("Minver: type = %s, NBANKS = %d, DIM = %d\n" \
                          % (valsType[i], nbanksList[j], dimList[k]))
                    print("APP: %s" % (app))                    
                    print("*******************************************\n")                

                    # Update the benchmark.h file

                    update_header(keywordsDefine, valsDefine, keywordsTypes[0], valsType[i])   

                    # Project name string
                    
                    project = ('minver_{type}_{nbank}b_{dim}x{dim}') \
                              .format(type = valsType[i], nbank=nbanksList[j], dim=dimList[k])

                    [compute_time, transfer_time, retries] = run_benchmark(project, app, synth, hw_test)

                    if retries > 0:

                        # Success

                        print("The number of cycles for computation is: %d" % (compute_time))
                        print("The number of cycles for transfer is: %d" % (transfer_time))

                        computeArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = compute_time
                        transferArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = transfer_time
                        totalArray[k + j*len(dimList) + i * len(nbanksList) * len(dimList)][g] = transfer_time + compute_time

                        # Add {dim}x{dim} (e.g. 4x4)
                        # add 1 is for alignment                       

                        csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) + 1][2] \
                                   = ('{dim}x{dim}').format(dim=dimList[k])   

            # Add NBANKS={nbank} (e.g. NBANKS=5)                                   
            # add 2 is for alignment

            csv_rows[k + j * len(dimList) + i * len(nbanksList) * len(dimList) - len(dimList) + 2][1] \
                       = ('NBANKS={nbank}').format(nbank = nbanksList[j])

        # Add Type={type} (e.g. Type=int)                                   
        # add 1 is for alignment                       

        csv_rows[i * len(nbanksList) * len(dimList) + 1][0] \
                   = ('Type={type}').format(type = valsType[i])                       

    # We now vertically stack the appList first and then the dataArray

    store_benchmark("minver", appList, computeArray, transferArray, totalArray, csv_rows)

def main(): 

    matmul(synth = 1, hw_test = 0)
    #minver(synth = 0, hw_test = 0)

if __name__ == "__main__":
    sys.exit(main())    