'''
Title: Gender Classifier
Author: Lasha Zakariashvili
Description: The purpose of this script is to take a corpus (each element seperated by
	a newline (\n) and output a "category.data" file which prints the category of each
	element seperated by a space.
	
Usage:	categorizer.py (optional: -v for verbose_mode mode) [training_corpus_location] [test_corpus_location]
'''

import sys
#from sklearn.feature_extraction.text import CountVectorizer
from text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from sklearn.datasets import load_files

verbose_mode = False

#==================================================================
#Load Data
#==================================================================
try:
	# Check if 3 arguments were passed
	if (len(sys.argv) == 4):
	
		#Check if the verbose command was passed
		if (sys.argv[1] == "-v"):
			verbose_mode = True
			trainset_location = sys.argv[2]
			dataset_location = sys.argv[3]
			
		#If not, then whatever user passed isn't valid
		else:
			raise ValueError("Three arguments, but the first one doesn't make sense!")
			
	# If 2 arguments, attempt to save file locations
	else:		
		trainset_location = sys.argv[1]
		dataset_location = sys.argv[2]
except IndexError:
    print "[ERROR] Invalid arguments passed!"
    print "[HINT] python categorizer.py [training_folder] [dataset_file]"
    sys.exit()
except ValueError as err:
    print ("[ERROR] %r" % (err.args))
    print "[HINT] python categorizer.py -v [training_folder] [dataset_file]"
    sys.exit()

#This needs some exception handling
with open(dataset_location) as f:
    content = f.readlines()
if (verbose_mode == True): 
	print "[STATUS] Read file successfully"
	for i in content:
		print ("[INPUT] %s" % i),
	print ('\n'),

#==================================================================
#Training the classifier (temporary! not to be used on 
#==================================================================
training_set = load_files(trainset_location)
classifier = Pipeline([('vect', CountVectorizer()),
                      ('tfidf', TfidfTransformer()),
                      ('clf', MultinomialNB()),
])
classifier = classifier.fit(training_set.data, training_set.target)


#==================================================================
#Apply prediction to the dataset
#==================================================================
predicted = classifier.predict(content)



#==================================================================
#Print prediction to document
#==================================================================
	
fileOut = open('test.data', 'w')
if verbose_mode is True:
	print "[STATUS] Writing to file."
#Print out possible categories on the first line
if verbose_mode is True:
	print ("[OUTPUT]"),
for c in training_set.target_names:
	fileOut.write(c + '\t')
	if verbose_mode is True:
		print(c),
fileOut.write('\n')
if verbose_mode is True:
	print ('\n'),

#Print out each category (array #) corresponding to each line in corpus
if verbose_mode is True:
	print "[OUTPUT]",
for c in predicted:
	fileOut.write('%r ' % c)
	if verbose_mode is True:
		print('%r ' % c),
fileOut.close()
	
'''
	You can use:

>>> from sklearn.externals import joblib
>>> joblib.dump(clf, 'my_model.pkl', compress=9)
And then later, on the prediction server:

>>> from sklearn.externals import joblib
>>> model_clone = joblib.load('my_model.pkl')
'''