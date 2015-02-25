/*
Title: Short Text Classification Accompanying WordNet
Directed By: Dr. Sarah Zelikovitz
Author: Lasha Zakariashvili

* The following c++ code is part of a text categorization research project
* directed by Dr. Sarah Zelikovitz.
* The intent of this portion of the project is to build on a given set of data
* (specifically a list of words) by adding words to the list that bare distinct
* similarities to the list, depending on what type of similarity we are testing.
* (IE synonyms, hyponyms, etc...) This will be done by opening a program known as WordNet
* from within our program to obtain the new words. The implementation of this code should
* result in a strengthening of our known data set.
*/

//includes needed to compile on UNIX: cstdlib, cstring.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include "porter2_stemmer.h"

using namespace std;

int main() {
	ifstream input;									//Will be used for opening the WN output file
	ofstream output;
	vector<string> Filtered_WN_Words;				//Will be used for storing filtered WN output words
	char word[32];									//Array to store user's word
	char cmd[128] = "wn ";							//Array to store UNIX command
	
	//----Obtaining WordNetOutput.txt from WordNet ----
	cout << "Please enter a word: ";
	cin >> word;									//Retrieving input word to use on WordNet
	strcat(cmd, word);
	strcat(cmd, " -grepn > WordNetOutput.txt");	
	cout << "Alright, processing word...\n";
	system(cmd);									//Calling WN command in UNIX
	//------------------------------------------------



	//--Stripping WordNetOutput.txt from redundant text---
	input.open("WordNetOutput.txt");
	string tmp;

	getline(input, tmp, '\n');
	getline(input, tmp, '\n');
	while (!input.eof()) {
		getline(input, tmp);
		Filtered_WN_Words.push_back(tmp);
	}
	input.close();
	output.open("WordNetOutput.txt");
	for (vector<string>::const_iterator i = Filtered_WN_Words.begin(); i != Filtered_WN_Words.end(); i++) {
		output << *i << '\n';
	}
	output.close();
	while (Filtered_WN_Words.size() != 0) {
		Filtered_WN_Words.pop_back();
	}
	//---------------------------------------------------



	//Apply Stemmer here??


	system("pause");
	return 0;
}