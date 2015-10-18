'''
Title: Gender Classifier
Author: Lasha Zakariashvili
Description: The purpose of this script is to take a corpus (each element seperated by
	a newline (\n) and output a "category.data" file which prints the category of each
	element seperated by a space.
	
Usage:	classify.py [-v(erbose)] [classifier_folder] [dataset_file] [output_prediction]
'''

import sys
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from sklearn.datasets import load_files
from sklearn.externals import joblib

from sklearn.externals import joblib

verbose_mode = False
def print_status(step):
	if (verbose_mode == True):
		if (step == 1):
			print "[STATUS] Read dataset file successfully"
			for i in content:
				print ("[INPUT] %s" % i),
			print ('\n'),
		elif (step == 2):
			print "[STATUS] Loaded classifier and training_set successfully."
		elif (step == 3):
			print "[STATUS] Classifier has applied prediction to dataset."
		elif (step == 4):
			print "[STATUS] Writing to output file."
		elif (step == 5):
			print ("[OUTPUT] "),
			for c in training_set.target_names:
				print(c),
			print('\n')
		elif (step == 6):
			print ("[OUTPUT] "),
			for c in predicted:
				print('%r ' % c),
			print('\n')
		elif (step == 7):
			print "[STATUS] File was written."
			print "[STATUS] Job complete."
	else:
		return


#==================================================================
#Load Data
#==================================================================
#First check arguments passed to script
try:
	# Check if 3 arguments were passed
	if (len(sys.argv) == 5):
	
		#Check if the verbose command was passed
		if (sys.argv[1] == "-v"):
			verbose_mode = True
			classifier_folder = sys.argv[2]
			dataset_location = sys.argv[3]
			output_name = sys.argv[4]
			
		#If not, then whatever user passed isn't valid
		else:
			raise ValueError("First argument isn't valid")
			
	# If 2 arguments, attempt to save file locations
	else:		
		classifier_folder = sys.argv[1]
		dataset_location = sys.argv[2]
		output_name = sys.argv[3]
except IndexError:
    print "[ERROR] Invalid arguments passed!"
    print "[HINT] classify.py [-v(erbose)] [classifier_folder] [dataset_file] [output_name]"
    sys.exit()
except ValueError as err:
    print ("[ERROR] %r" % (err.args))
    print "[HINT] Did you mean to pass '-v' as the first argument?"
    sys.exit()

try:
	with open(dataset_location) as f:
		content = f.readlines()
	print_status(1)
except:
	print "[ERROR] There was an issue reading the dataset file!"
	sys.exit()

#==================================================================
#Apply prediction to the dataset
#==================================================================

classifier = joblib.load(classifier_folder + '/classifier.pkl')
training_set = joblib.load(classifier_folder + '/training_set.pkl')
print_status(2)
predicted = classifier.predict(content)
print_status(3)

#==================================================================
#Print prediction to document
#==================================================================
	

#this part needs some cleanup.
fileOut = open(output_name, 'w')
print_status(4)

#Print out possible categories on the first line

for c in training_set.target_names:
	fileOut.write(c + '\t')
fileOut.write('\n')
print_status(5)
#Print out each category (array #) corresponding to each line in corpus
for c in predicted:
	fileOut.write('%r ' % c)
print_status(6)
fileOut.close()
print_status(7)

