#!/usr/bin/python3

import re
import os
import sys
import subprocess
import numpy as np

# clean_up() removes the log and journal files made by vivado

def clean_up():

	filelist = [ f for f in os.listdir(".") if (f.endswith(".log") 
											or f.endswith(".jou")) ]
	for f in filelist:
		os.remove(f)        

# update_header() update updates the header file

def update_header(keywordsDefine, valsDefine, keywordsTypes, valsType):

	with open('c/libhwa/benchmark.h','r') as f1, \
		 open('c/libhwa/benchmark.xh','w') as f2:

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

# run_benchmark() executes the cmd in the terminal

def run_benchmark(project, app, synth, hw_test):

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

		result = subprocess.run([cmd], stdout=subprocess.PIPE, 
								stderr=subprocess.PIPE, shell=True)

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

			compute_time = int((re.search('<compute>(.*)</compute>', 
								result)).group(1))

			transfer_time = int((re.search('<transfer>(.*)</transfer>', 
								 result)).group(1))

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

# store_benchmark() stores the benchmark data in .csv format    

def store_benchmark(bench_name, appList, computeArray, 
					transferArray, totalArray, csv_rows):

	computeOut = np.vstack((appList, computeArray))
	computeOut = np.hstack((csv_rows, computeOut))

	transferOut = np.vstack((appList, transferArray))
	transferOut = np.hstack((csv_rows, transferOut))

	totalOut = np.vstack((appList, totalArray))
	totalOut = np.hstack((csv_rows, totalOut))    

	dataOut = np.vstack((computeOut, transferOut, totalOut))

	try:
		os.remove('reports/' + bench_name + '_compute.csv')	# Delete old
	except:
		print("Deleting file")

	try:
		os.remove('reports/' + bench_name + '_transfer.csv')	# Delete old
	except:
		print("Deleting file")

	try:
		os.remove('reports/' + bench_name + '.csv')	# Delete old
	except:
		print("Deleting file")		

	np.savetxt('reports/' + bench_name + '_compute.csv', 
			   computeOut, delimiter=',', fmt='%s') 

	np.savetxt('reports/' + bench_name + '_transfer.csv', 
			   transferOut, delimiter=',', fmt='%s') 

	np.savetxt('reports/' + bench_name + '.csv', dataOut, delimiter=',', fmt='%s') 

# matmul() is used to run the benchmarks for matrix multiplication

def matmul(synth = 0, hw_test = 0):

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for matrix multiplication

	appList     = ["hwa_matmul", "hwa_matmul_spm", 
				   "tacle_matrix1", "tacle_matrix1_spm"]

	# Arrays for data storage

	computeArray = np.zeros([1, len(appList)])
	transferArray = np.zeros([1, len(appList)]) 
	totalArray = np.zeros([1, len(appList)]) 

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		app = appList[i]
		valsDefine = [32, 32, 32, 9, 1024, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0] # Vectors not used

		print("\n*******************************************")
		print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" \
			  % ("int", 9, 32))
		print("APP: %s" % (app))                    
		print("*******************************************\n")

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type", "int")

		# Project name string

		project = ('matmul_{type}_{nbank}b_{dim}x{dim}_mcu') \
				  .format(type = "int", nbank=9, dim=32)

		[compute_time, transfer_time, retries] \
			= run_benchmark(project, app, synth, hw_test)

		if retries > 0:

			# Success

			print("#cycles computation: %d" % (compute_time))
			print("#cycles transfer: %d" % (transfer_time))

			total_time = transfer_time + compute_time

			computeArray[0][i] = compute_time
			transferArray[0][i] = transfer_time
			totalArray[0][i] = total_time 

	store_benchmark("matmul_mcu", appList, computeArray, 
					transferArray, totalArray, csv_rows)


def filterbank(synth = 0, hw_test = 0):

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_filterbank", "hwa_filterbank_spm", "tacle_filterbank", 
			   "tacle_filterbank_spm"] 

	# Arrays for data storage

	computeArray = np.zeros([1, len(appList)])
	transferArray = np.zeros([1, len(appList)]) 
	totalArray = np.zeros([1, len(appList)]) 

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]
		valsDefine = [32, 8, 32, 4, 256, 256, 0,
						0, 0, 0, 0, 0, 0, 0, 0]                    

		print("\n*******************************************")
		print("Filterbank: type = %s, NBANKS = %d\n" \
			  % ("int", 4))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")   

		# Project name string
		
		project = ('filterbank_{type}_mcu') \
				  .format(type = "int")

		[compute_time, transfer_time, retries] \
			= run_benchmark(project, app, synth, hw_test)

		if retries > 0:

			# Success

			print("#cycles computation: %d" % (compute_time))
			print("#cycles transfer: %d" % (transfer_time))

			total_time = transfer_time + compute_time

			computeArray[0][i] = compute_time
			transferArray[0][i] = transfer_time
			totalArray[0][i] = total_time 

	store_benchmark("filterbank_mcu", appList, computeArray, 
					transferArray, totalArray, csv_rows)

def fir2dim(synth = 0, hw_test = 0):

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_fir2dim", "hwa_fir2dim_spm", 
			   "tacle_fir2dim", "tacle_fir2dim_spm"] 

	# Arrays for data storage

	computeArray = np.zeros([1, len(appList)])
	transferArray = np.zeros([1, len(appList)]) 
	totalArray = np.zeros([1, len(appList)]) 

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]
		valsDefine = [1, 1, 1, 2, 61, 61, 0,
						0, 0, 0, 0, 0, 0, 0, 0] #NBANKS is the only one really used
										 #VECSIZE is for WCET analysis            

		print("\n*******************************************")
		print("Fir2dim: type = %s, NBANKS = %d\n" \
			  % ("int", 2))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")   

		# Project name string
		
		project = ('fir2dim_{type}_mcu') \
				  .format(type = "int")

		[compute_time, transfer_time, retries] \
			= run_benchmark(project, app, synth, hw_test)

		if retries > 0:

			# Success

			print("#cycles computation: %d" % (compute_time))
			print("#cycles transfer: %d" % (transfer_time))

			total_time = transfer_time + compute_time

			computeArray[0][i] = compute_time
			transferArray[0][i] = transfer_time
			totalArray[0][i] = total_time 

	store_benchmark("fir2dim_mcu", appList, computeArray, 
					transferArray, totalArray, csv_rows)

def adpcm(synth = 0, hw_test = 0):

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_adpcm_encode", "hwa_adpcm_encode_spm",
			    "hwa_adpcm_decode", "hwa_adpcm_decode_spm",
			   "tacle_adpcm_enc", "tacle_adpcm_enc_spm",
			   "tacle_adpcm_dec", "tacle_adpcm_dec_spm"] 

	# Arrays for data storage

	computeArray = np.zeros([1, len(appList)])
	transferArray = np.zeros([1, len(appList)]) 
	totalArray = np.zeros([1, len(appList)]) 

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]
		valsDefine = [3, 3, 3, 3, 9, 3, 0,
						0, 0, 0, 0, 0, 0, 0, 0]

		print("\n*******************************************")
		print("ADPCM: type = %s, NBANKS = %d\n" \
			  % ("int", 3))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")   

		# Project name string
		
		project = ('adpcm_mcu')

		[compute_time, transfer_time, retries] \
			= run_benchmark(project, app, synth, hw_test)

		if retries > 0:

			# Success

			print("#cycles computation: %d" % (compute_time))
			print("#cycles transfer: %d" % (transfer_time))

			total_time = transfer_time + compute_time

			computeArray[0][i] = compute_time
			transferArray[0][i] = transfer_time
			totalArray[0][i] = total_time 

	store_benchmark("adpcm_mcu", appList, computeArray, 
					transferArray, totalArray, csv_rows)		


def run_wcet(app, function):

	# Project name string

	cmd = ('make -B APP=wcet-{app} comp') \
			.format(app = app)

	subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)				

	cmd = ('(cd wcet; make wcet PROJECT?={app} FUNCTION?={func} )').format(app = app, func =function)

	result = subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

	result = result.stderr.decode('utf-8') 

	wcet_bound = 0

	try:

		wcet_bound = int((re.search('bound: (.*) cycles', result)).group(1))

	except:
		print("Error when getting the number of cycles")
		print(result)

	# Success

	print("#WCET bound: %d" % (wcet_bound))	

	return wcet_bound	

def store_wcet_benchmark(bench_name, appList, dataArray, csv_rows):

	dataOut = np.vstack((appList, dataArray))
	dataOut = np.hstack((csv_rows, dataOut))

	try:
		os.remove('reports/' + bench_name + '_wcet.csv')	# Delete old
	except:
		print("Deleting file")

	np.savetxt('reports/' + bench_name + '_wcet.csv', dataOut, delimiter=',', fmt='%s') 

def matmul_wcet():

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for matrix multiplication

	appList     = ["hwa_matmul", "hwa_matmul_spm",
				   "tacle_matrix1", "tacle_matrix1_spm"]

	functionList = ["matmul_main_wcet", "matrix1_main"]

	app_type = [0, 0, 1, 1] # 0 is for hardware

	# Arrays for data storage

	dataArray = np.zeros([1, len(appList)])

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]

		valsDefine = [32, 32, 32, 9, 1024, 0, 1, 4, 8, 1, 32, 0, 0, 0, 0]

		print("\n*******************************************")
		print("Matmul: type = %s, NBANKS = %d, DIM = %d\n" \
			  % ("int", 9, 32))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                     

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")  

		wcet_bound = run_wcet(app, functionList[app_type[i]])
 
		dataArray[0][i] = wcet_bound                    

	store_wcet_benchmark("matmul_mcu", appList, dataArray, csv_rows)

def filterbank_wcet():

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_filterbank", "hwa_filterbank_spm", 
			   "tacle_filterbank", "tacle_filterbank_spm"] 

	functionList = ["filterbank_main_wcet", "filterbank_main"]			   

	app_type = [0, 0, 1, 1] # 0 is for hardware

	# Arrays for data storage

	dataArray = np.zeros([1, len(appList)])

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]
		valsDefine = [32, 8, 32, 4, 256, 256, 1,
						1, 32, 1, 32,
						1, 256, 1, 256]                    

		print("\n*******************************************")
		print("Filterbank WCET: type = %s, NBANKS = %d\n" \
			  % ("int", 4))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")  

		wcet_bound = run_wcet(app, functionList[app_type[i]])
 
		dataArray[0][i] = wcet_bound

	store_wcet_benchmark("filterbank_mcu", appList, dataArray, csv_rows)


def fir2dim_wcet():

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_fir2dim", "hwa_fir2dim_spm", "tacle_fir2dim", 
			   "tacle_fir2dim_spm"] 

	functionList = ["fir2dim_main_wcet", "fir2dim_main"]			   

	app_type = [0, 0, 1, 1] # 0 is for hardware

	# Arrays for data storage

	dataArray = np.zeros([1, len(appList)])

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]
		#NBANKS is the only one really used
		 #VECSIZE is for WCET analysis 

		valsDefine = [1, 1, 1, 2, 61, 61, 1,
						0, 0, 0, 0,
						1, 61, 1, 16] 				   

		print("\n*******************************************")
		print("Fir2Dim: type = %s, NBANKS = %d\n" \
			  % ("int", 2))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")   

		wcet_bound = run_wcet(app, functionList[app_type[i]])
 
		dataArray[0][i] = wcet_bound

	store_wcet_benchmark("fir2dim_mcu", appList, dataArray, csv_rows)

def adpcm_enc_wcet():


	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_adpcm_encode", "hwa_adpcm_encode_spm", 
			   "tacle_adpcm_enc", "tacle_adpcm_enc_spm"] 

	functionList = ["adpcm_main_wcet", "adpcm_enc_main"]			   

	app_type = [0, 0, 1, 1] # 0 is for hardware

	# Arrays for data storage

	dataArray = np.zeros([1, len(appList)])

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]

		valsDefine = [3, 3, 3, 3, 9, 3, 1,
						1, 3, 1, 3,
						1, 3, 1, 3] 	

		print("\n*******************************************")
		print("ADPCM: type = %s, NBANKS = %d\n" \
			  % ("int", 3))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")   

		wcet_bound = run_wcet(app, functionList[app_type[i]])
 
		dataArray[0][i] = wcet_bound	

	store_wcet_benchmark("adpcm_enc_mcu", appList, dataArray, csv_rows)	

def adpcm_dec_wcet():

	# These lists holds the definitions for the
	# defines and typedefs to be changed

	keywordsDefine  = ["DIM", "ROWS", "COLS", "NBANKS", "SIZE", "VECSIZE", "WCET",
						"ARRAY_WR_FACTOR", "ARRAY_WR_DIV", "ARRAY_RD_FACTOR", "ARRAY_RD_DIV",
						"VEC_WR_FACTOR", "VEC_WR_DIV", "VEC_RD_FACTOR", "VEC_RD_DIV"]

	# Parameter space to explore for filterbank

	appList = ["hwa_adpcm_decode", "hwa_adpcm_decode_spm", 
			   "tacle_adpcm_dec", "tacle_adpcm_dec_spm"] 

	functionList = ["adpcm_main_wcet", "adpcm_dec_main"]			   

	app_type = [0, 0, 1, 1] # 0 is for hardware

	# Arrays for data storage

	dataArray = np.zeros([1, len(appList)])

	# Add 1 since it will be horizontally stacked later
	# max string length of 10

	csv_rows = np.zeros([2, 1], dtype = "S10") 

	for i in range(0, len(appList)):    # Iterate over apps      

		# Get the current iteration options      

		app = appList[i]

		valsDefine = [3, 3, 3, 3, 9, 3, 1,
						1, 3, 1, 3,
						1, 3, 1, 3] 	

		print("\n*******************************************")
		print("ADPCM: type = %s, NBANKS = %d\n" \
			  % ("int", 3))
		print("APP: %s" % (app))                    
		print("*******************************************\n")                

		# Update the benchmark.h file

		update_header(keywordsDefine, valsDefine, "mat_type;", "int")

		wcet_bound = run_wcet(app, functionList[app_type[i]])
 
		dataArray[0][i] = wcet_bound	

	store_wcet_benchmark("adpcm_dec_mcu", appList, dataArray, csv_rows)	


def main(): 

	#matmul(synth = 0, hw_test = 0)
	#filterbank(synth = 0, hw_test = 0)
	#fir2dim(synth = 0, hw_test = 0)
	#adpcm(synth = 0, hw_test = 0)

	#matmul_wcet()
	filterbank_wcet()
	fir2dim_wcet()
	adpcm_dec_wcet()
	adpcm_enc_wcet()

	clean_up()

if __name__ == "__main__":
	sys.exit(main())