/*
	//----------------------------------------------------------------------------------------
	Title: WordNet Hyponym Extractor
	Author: Lasha Zakariashvili

	Description: The purpose of the function getHypon is to load a sample corpus, then process
		each individual word through WordNet and temporarily save to WN_Output.tmp. After this 
		is complete, the function will extract the useful words and place them into a set. 
		Once this is complete, the function will output the set (starting with the main word) 
		into the specified file.

	Usage:	getHypon("read_from_file", "save_as_file");  //nothing is return, file is produced

	**NOTE: Make sure WordNet is properly installed and the PATH is set for terminal to use **

	Exception Codes:
		[NONE ATM, WILL ADD SOON]
	//----------------------------------------------------------------------------------------
*/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <set>
using namespace std;
extern char list_delim;

//Obtains the file size
extern std::ifstream::pos_type filesize(const char* filename);

void getHypons(string read_from_file, string save_as_file) {

	set<string> list;				//To temporarily store stripped words
	ifstream input;					//To read file given and extract words
	ofstream output;				//To later output set<string> list
	char cmd[128] = "";				//Array to store UNIX command
	char word[32] = "";				//Array to store stripped words
	char main_word[32] = "";		//Array to store main word (each word from read_from_file)
	char tmp[2] = " ";				//Array to append each character

	input.open(read_from_file.c_str());
	if (!input) {
		cout << "File input not found, terminating process!";
		//******************************* [THROW EXCEPTION HERE]  ***************************** <--
	}

	//----------------------------------------------------------------------------------------
	//-------------------CREATED + RUNNING COMMAND THROUGH TERMINAL---------------------------
	//----------------------------------------------------------------------------------------

	//while (not at end of file     &&     (read_from_file size) - (stream position) != 1
	while (!input.eof() && !((filesize(read_from_file.c_str())-input.tellg()) == 1)) {
		input >> main_word;
		strcpy(cmd, "wn ");
		strcat(cmd, main_word);
		strcat(cmd, " -a -hypon -treen > WN_Output.tmp");
		//Run command through terminal
		system(cmd);
		
		//----------------------------------------------------------------------------------------
		//---------------------THIS WILL STRIP THE WN OUTPUT AND ADD TO SET-----------------------
		//----------------------------------------------------------------------------------------
		if (filesize("WN_Output.tmp") != (static_cast<std::ifstream::pos_type>(0))) {
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
		output << main_word << '\n';
		if (!list.empty()) {
			for (set<string>::const_iterator i = list.begin(); i != list.end(); i++) {
				output << *i << '\n';
			}
		}
		output << list_delim << '\n';
		output.close();
		list.clear();
		remove("WN_Output.tmp");
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------
	} //Go back to -> while (!input.eof())
}

/*	[CURRENTLY DISABLED TO PREVENT MISUSE]

void getHypon(string read_as_file) {
	getHypon(read_as_file, read_as_file);
}
*/
