/*
	Title: Short Text Classification Accompanying WordNet
	Directed By: Dr. Sarah Zelikovitz
	Author: Lasha Zakariashvili

	Description: A different approach to stripping words (i will come up with better desc. later)

*/

//includes needed to compile on UNIX: cstdlib, cstring.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include "porter2_stemmer.h"

using namespace std;

extern void WNStrip(string);
extern void WNStrip(string, string);

int main() {

	char word[32] = "";									//Array to store user's WN search word
	char cmd[128] = "wn ";							//Array to store UNIX command
	char file[128] = "";
	
	//------Menu-----------
	cout << "\n---Short Text Classifier---\n"
		 << "By: Lasha Zakariashvili\n\n"
		 << "How to use: Have a short list of words ready to be loaded (seperated by spaces)."
		 << "After the file is processed, it will output another file which compressed the previous file given.\n\n"
		 << "Please enter filename: ";
	cin >> file;
	


	//----Obtaining WordNetOutput.txt from WordNet ----
	cin >> word;									//Retrieving input word to use on WordNet
	strcat(cmd, word);								//Creating command that will be ran through UNIX
	strcat(cmd, " -a -hypon -treen > WordNetOutput.txt");
	//strcat(cmd, word);							//Later, for custom file names
	//strcat(cmd, "\".txt");
	cout << "Alright, obtaining file from WordNet...\n";
	system(cmd);									//Calling WN command in UNIX
	//------------------------------------------------
	

	cout << "Stripping redundant text...\n";
	WNStrip("WordNetOutput.txt");


	system("pause");
	return 0;
}