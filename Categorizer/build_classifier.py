'''
Title: Gender Classifier
Author: Lasha Zakariashvili
Description: The purpose of this script is to take an already labeled set of training
	data and have the machine learn it (applying Naive Bayes) and then exporting the
	classifier to the specified filename.
	
Usage:	categorizer.py [-v(erbose)] [training_corpus_location] [output_name]
'''

import sys
import os
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from sklearn.datasets import load_files

from sklearn.externals import joblib

verbose_mode = False
def print_status(step):
	if (verbose_mode == True):
		if (step == 1):
			print "[INFO] Training folder loaded successfully."
		elif (step == 2):
			print "[INFO] Classifier has been trained."
		elif (step == 3):
			print "[INFO] Exported the classifier to " + output_name + ".pkl"
	else:
		return

#==================================================================
#Load Data
#==================================================================
#First check arguments passed to script
try:
	# Check if 3 arguments were passed
	if (len(sys.argv) == 4):
	
		#Check if the verbose command was passed
		if (sys.argv[1] == "-v"):
			verbose_mode = True
			trainset_location = sys.argv[2]
			output_name = sys.argv[3]
			
		#If not, then whatever user passed isn't valid
		else:
			raise ValueError("First argument isn't valid")
			
	# If 2 arguments, attempt to save file locations
	else:		
		trainset_location = sys.argv[1]
		output_name = sys.argv[2]
except IndexError:
    print "[ERROR] Invalid arguments passed!"
    print "[HINT] python build_classifier.py [-v(erbose)] [training_folder] [output_name]"
    sys.exit()
except ValueError as err:
    print ("[ERROR] %r" % (err.args))
    print "[HINT] Did you mean to pass '-v' as the first argument?"
    sys.exit()


#==================================================================
#Training the classifier
#==================================================================
try:
	training_set = load_files(trainset_location)
	print_status(1)
except OSError:
	print "[ERROR] Training folder could not be open!"
	print "[HINT] Did you spell the folder correctly?"
	sys.exit()

training_set = load_files(trainset_location)
classifier = Pipeline([('vect', CountVectorizer()),
                      ('tfidf', TfidfTransformer()),
                      ('clf', MultinomialNB()),
])
classifier = classifier.fit(training_set.data, training_set.target)
print_status(2)
if not os.path.exists(output_name):
    os.makedirs(output_name)
joblib.dump(training_set, output_name + '/training_set.pkl', compress=9)
joblib.dump(classifier, output_name + '/classifier.pkl', compress=9)
print_status(3)

sys.exit()




