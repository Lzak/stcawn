/*
	Title: Short Text Classification Accompanying WordNet
	Directed By: Dr. Sarah Zelikovitz
	Author: Lasha Zakariashvili

	Description: One day I'll stop being lazy and actually write a description
*/

//includes needed to compile on UNIX: cstdlib, cstring.
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

std::ifstream::pos_type filesize(const char* filename) {
	ifstream in(filename, ifstream::ate | ifstream::binary);
	return in.tellg();
}
extern void getHypons(string, string);
extern void compress(string);
char list_delim = '$';


int main() {

	char input_file_name[128] = "";			//Array to store the input file name (FROM file)
	char output_file_name[128] = "";		//Array to store the output file name (TO file)
	ifstream input;
	

	//------Menu-----------
	cout << "\n---Short Text Classifier---\n"
		<< "By: Lasha Zakariashvili\n\n"
		<< "How to use: Have a short list of words ready to be loaded (seperated\n"
		<< "by spaces). After the file is processed, it will output another file\n"
		<< "which compressed the previous file given.\n\n"

		<< "Please enter input filename: ";
	cin >> input_file_name;
	cout << "Please enter output filename: ";
	cin >> output_file_name;



	//-------Call to getHypon---------
	getHypons(input_file_name, output_file_name);
	compress(output_file_name);
	cout << "Job complete!\n";
	system("pause");
	return 0;
}
