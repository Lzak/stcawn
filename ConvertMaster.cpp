/*
	//----------------------------------------------------------------------------------------
	Title: Root Word Converter (needs a better name ik)
	Author: Lasha Zakariashvili

	Description: The purpose of the function is to export the original corpus words in terms
		of similarities amongst each other. If no similarities are present, then the word will
		remain unchanged. If this is unclear, see main.cpp for purpose of each .cpp file.
		
	Usage:

	//----------------------------------------------------------------------------------------
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

void convertMaster(string input_file_name) {
	vector<vector<string>> hypon_list;
	vector<vector<string>>::iterator iter1;
	vector<string>::iterator iter2;
	string word = "test";
	int size[2];
	

	ifstream input(input_file_name);
	if (!input) {
		cout << "Code Hippo!";
		return;
	}


	//this gonna get messy ;)
	cout << "#1\n";

	while (!input.eof() && word != "-") {
		cout << "#2\n";

		vector<string> tmp_vec;
		while (word != "-" && word != "") {
			cout << "#3\n";
			getline(input, word, '\n');
			tmp_vec.push_back(word);
			cout << word << endl;
		}
		hypon_list.push_back(tmp_vec);
	}


	cout << "#4\n";
	size[0] = hypon_list.size();
	for (int i = 0; i < size[0]; i++) {
		size[1] = hypon_list[i].size();
		for (int j = 0; j < size[1]; j++) {
			cout << hypon_list[i][j] << endl;
		}

	}

}
