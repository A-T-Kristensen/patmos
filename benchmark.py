import re
import os
import sys
import subprocess

# Run with python3

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
	                val = str(valsType[keywordsTypes.index(s[2])]) # Index into vals in the same position as keyword	            
	                line = re.sub(r'({0}\s+)[a-zA-Z0-9"]+'.format(s[0]),r"\g<1>{0}".format(val),line)
	            f2.write(line) 	        

	f1.close()
	f2.close()

def update_test():

	NBANKS = [3, 5, 7]
	DIM = [4, 16, 32]

	keywordsDefine=["DIM","NBANKS"]
	keywordsTypes = ["mat_type;","vec_type;"]

	valsDefine=[DIM[1],NBANKS[0]]    # Make a set of vals depending on test
	valsType = ["float"]

	update(keywordsDefine, valsDefine, keywordsTypes, valsType)

	os.remove('c/benchmark.h')
	os.rename('c/benchmark.xh', 'c/benchmark.h')

	app = "hwa_matmul_nb"
	project = "matmul_float_3b_16x16"

	cmd = ('make COM_PORT?=/dev/ttyUSB1 '
			'HWA_PROJECT={prj} '
			'APP={app} '
			'comp hwa_config download').format(prj=project, app = app)

	#os.system(cmd)
	result = subprocess.run([cmd], stdout=subprocess.PIPE, shell=True)	

	test = result.stdout.decode('utf-8')

	print(test.partition("HWA Running")[2]) # Print everything after HWA Running

	#result = subprocess.Popen([cmd], stdout=subprocess.PIPE, 
                                    #stderr=subprocess.PIPE)	

	#out, err = p.communicate()

	#print out


def main():	
	update_test()

if __name__ == "__main__":
    sys.exit(main())	


