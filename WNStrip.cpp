/*
	Title: WordNet Text Stripper
	Author: Lasha Zakariashvili

	Description: [MUST UPDATE]

	Usage:	[MUST UPDATE]
*/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <set>
using namespace std;

void WNStrip(string read_from_file, string save_as_file) {

	set<string> list;				//To temporarily store stripped words
	ifstream input;					//To read file given and extract words
	ofstream output;				//To later output set<string> list
	char cmd[128] = "";				//Array to store UNIX command
	char word[32] = "";
	char tmp[2] = " ";

	input.open(read_from_file.c_str());
	if (!input) {
		cout << "File input not found, terminating process!";
		//[ADD EXCEPTION HERE]
	}

	while (!input.eof()) {
		//Creating a command string to run through UNIX
		input >> word;
		strcpy(cmd, "wn ");
		strcat(cmd, word);
		strcat(cmd, " -a -hypon -treen > WN_Output.tmp");
		cout << cmd << '\n';													 //[FOR DEBUGGING]
		//WNStrip(output, cmd);
		//system(cmd);															   [FOR DEBUGGING]


		//----------------------------------------------------------------------------------------
		//----------------THIS WILL STRIP THE OUTPUT FROM REDUNDANT TEXT--------------------------
		//----------------------------------------------------------------------------------------
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
		//----------------------------------------------------------------------------------------
		//-----------------THIS WILL EXPORT THE STIPPED WORDS INTO A CLEAN FILE-------------------
		//----------------------------------------------------------------------------------------
		output.open(save_as_file.c_str(), ios::app);
		for (set<string>::const_iterator i = list.begin(); i != list.end(); i++) {
			output << *i << '\n';
		}
		output << "-\n";
		output.close();
		list.clear();
		remove("WN_Output.tmp");
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------
	} //Done reading input file
}

void WNStrip(string read_as_file) {
	WNStrip(read_as_file, read_as_file);
}
