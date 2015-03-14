/*
	//----------------------------------------------------------------------------------------
	Title: Hyponym Compressor
	Author: Lasha Zakariashvili

	Description: The purpose of this compressor is to import the hyponymic corpus into a
		vector of vector of strings (vector<vector<string>>), then analize the vectors for
		similarities. If similarities are present, the root word of the latter comparate will
		be renamed to the initial comparate. If no similarities are present, then the word
		will remain unchanged. The sorting style is similar to Insertion Sort.
		
	Usage:	compress(input_file_name);	//Caution: This will overwrite the file!

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
extern char list_delim;


//Obtains the file size
bool is_similar(vector<string>&, vector<string>&);
extern std::ifstream::pos_type filesize(const char* filename);

void compress(string input_file_name) {
	vector<vector<string> > hypon_list;
	string word = "test";
	int vector_size[2];
	

	ifstream input(input_file_name.c_str());
	if (!input) {
		cout << "File input not found, terminating process!";
		//MUST THROW EXCEP HERE
		return;
	}

	//----------------------------------------------------------------------------------------
	//----------LOAD WORDS INTO A VECTOR OF VECTOR (vector<vector<string> >-------------------
	//----------------------------------------------------------------------------------------
	while (input.tellg() < filesize(input_file_name.c_str())){
		vector<string> tmp_vec;
		while (input.peek() != list_delim) {
			getline(input, word, '\n');
			tmp_vec.push_back(word);
			cout << "Word: " << word << endl;
		}
		hypon_list.push_back(tmp_vec);
		getline(input, word, '\n');		//Collect the useless deliminator
	}									//(see list_delim variable)
	input.close();
	//----------------------------------------------------------------------------------------
	//----------------SORTING SIMILAR WORDS (Insertion Sort modification)---------------------
	//----------------------------------------------------------------------------------------
	vector_size[0] = hypon_list.size();
	int i, j;
	for (i = 1; i < vector_size[0]; i++) {
		j = 0;
		while (j < i) {
			//check if one vector is similar to another
			if (is_similar(hypon_list[i], hypon_list[j])) {
				//if it is, lets rename the root word
				hypon_list[i][0] = hypon_list[j][0];
				break;
			} else {
				j++;
			}
		}
	}
	
	//----------------------------------------------------------------------------------------
	//-----------------------BEGIN EXPORTING COMPRESSED ROOT WORDS----------------------------
	//----------------------------------------------------------------------------------------
	ofstream output(input_file_name.c_str());
	vector_size[0] = hypon_list.size();
	for (int i = 0; i < vector_size[0]; i++) {
		output << hypon_list[i][0] << endl;
	}
}

//Function to compare results
bool is_similar(vector<string>& vecA, vector<string>& vecB) {
	int vecA_size = vecA.size();
	int vecB_size = vecB.size();
	bool result = false;
	for (int i = 0; i < vecA_size; i++) {
		for (int j = 0; j < vecB_size; j++) {
			if (vecA[i] == vecB[j])
				result = true;
		}
	}
	return result;
}
