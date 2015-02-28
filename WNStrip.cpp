/*
	Title: WordNet Text Stripper
	Author: Lasha Zakariashvili

	Description: The functions in this CPP are for stripping
		the content of the WordNet output when run with the
		following parameters (although theoretically can be
		used with ANY parameters as long as -a is included):

			$ wn [word] -a -hypon -treen

		After the function have been executed, the file 
		that was opened will be overwritten with the list
		of words.

	Usage:	WNStrip(filename)
			WNStrip(filename, fileOutput)
*/


#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

void WNStrip(string read_from_file, string save_as_file) {
	set<string> list;				//To temporarily store stripped words
	ifstream input;					//To read file given and extract words
	ofstream output;				//To later output set<string> list
	char word[32] = "";
	char tmp[2] = "";
	input.open(read_from_file);

	while (!input.eof()) {

		//Search for <anything.anything>
		while (tmp[0] != '<' && !input.eof()) {
			input.get(tmp[0]);
		}

		//Get to the beginning of first word
		while (tmp[0] != ' ' && !input.eof()) {
			input.get(tmp[0]);
		}

		//Begin extracting all words on this line (up until '\n')
		tmp[0] = ' ';
		while (tmp[0] != '\n' && !input.eof()) {
			input.get(tmp[0]);
			if (tmp[0] != ',' && tmp[0] != '\n' && !input.eof()) {
				strcat(word, tmp);
			}
			else if (tmp[0] == ',' && !input.eof()) {
				list.insert(word);
				input.get(tmp[0]);
				strcpy(word, "");
			}
			else {
				list.insert(word);
			}
		}
		strcpy(word, "");
		//Repeat process for every line that has "< ... >" in it (unless EOF)
	}
	input.close();

	//Export everything stored in list set
	output.open(save_as_file, ios::app);
	for (set<string>::const_iterator i = list.begin(); i != list.end(); i++) {
		output << *i << '\n';
	}
	output << "-\n";
	output.close();
	list.clear();
}

void WNStrip(string read_as_file) {
	WNStrip("WN_Output.tmp", read_as_file);
}