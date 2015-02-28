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

std::ifstream::pos_type filesize(const char* filename) {
	ifstream in(filename, ifstream::ate | ifstream::binary);
	return in.tellg();
}

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

	while (!input.eof() && !((filesize(read_from_file.c_str())-input.tellg()) == 1)) {
		cout << "1) CURRENT COPRUS POS: " << input.tellg() << '\n';
		cout << "2) LAST CORPUS POS: " << filesize(read_from_file.c_str()) << '\n';
		cout << "2a) DIFFERENCE: " << filesize(read_from_file.c_str())-input.tellg() << endl;
		//Creating a command string to run through UNIX
		input >> word;
		strcpy(cmd, "wn ");
		strcat(cmd, word);
		strcat(cmd, " -a -hypon -treen > WN_Output.tmp");
		cout << cmd << '\n';
		//WNStrip(output, cmd);
		system(cmd);
		cout << "3) WN_Output.tmp Filesize: " << filesize("WN_Output.tmp") << '\n';

		if (filesize("WN_Output.tmp") == (static_cast<std::ifstream::pos_type>(0))) {
			cout << "4a) Went into IF statement\n";
			list.insert(word);
		} else {
			cout << "4b) Went into ELSE statement\n";
		//----------------------------------------------------------------------------------------
		//----------------THIS WILL STRIP THE OUTPUT FROM REDUNDANT TEXT--------------------------
		//----------------------------------------------------------------------------------------
			ifstream WN_input("WN_Output.tmp");
			while (!WN_input.eof()) {
				//Search for <anything.anything>
				while (tmp[0] != '<' && !WN_input.eof()) {
					WN_input.get(tmp[0]);
				}

				//Get to the beginning of first word
				while (tmp[0] != ' ' && !WN_input.eof()) {
					WN_input.get(tmp[0]);
				}

				//Begin extracting all words on this line (up until '\n')
				tmp[0] = ' ';
				while (tmp[0] != '\n' && !WN_input.eof()) {
					WN_input.get(tmp[0]);
					if (tmp[0] != ',' && tmp[0] != '\n' && !WN_input.eof()) {
						strcat(word, tmp);
					}
					else if (tmp[0] == ',' && !WN_input.eof()) {
						list.insert(word);
						WN_input.get(tmp[0]);
						strcpy(word, "");
					}
					else {
						list.insert(word);
					}
				}
				strcpy(word, "");
				//Repeat process for every line that has "< ... >" in it (unless EOF)
			}
			WN_input.close();
		}
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
		cout << "5) CURRENT COPRUS POS (end of while): " << input.tellg() << '\n';
	} //Go back to -> while (!input.eof())
}

void WNStrip(string read_as_file) {
	WNStrip(read_as_file, read_as_file);
}
