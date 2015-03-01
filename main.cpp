/*
	Title: Short Text Classification Accompanying WordNet
	Directed By: Dr. Sarah Zelikovitz
	Author: Lasha Zakariashvili

	Description: A different approach to stripping words (i will come up with better desc. later)
*/

//includes needed to compile on UNIX: cstdlib, cstring.
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

extern void getHypon(string);
extern void getHypon(string, string);

int main() {

	char filename_in[128] = "";			//Array to store the input file name (FROM file)
	char filename_out[128] = "";		//Array to store the output file name (TO file)
	ifstream input;
	
	//------Menu-----------
	cout << "\n---Short Text Classifier---\n"
		<< "By: Lasha Zakariashvili\n\n"
		<< "How to use: Have a short list of words ready to be loaded (seperated\n"
		<< "by spaces). After the file is processed, it will output another file\n"
		<< "which compressed the previous file given.\n\n"

		<< "Please enter input filename: ";
	cin >> filename_in;
	cout << "Please enter output filename: ";
	cin >> filename_out;

	//-------Call to getHypon---------
	getHypon(filename_in, filename_out);
	cout << "Done!\n";

	system("pause");
	return 0;
}
