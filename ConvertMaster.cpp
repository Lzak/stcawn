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
extern char list_delim;


//Obtains the file size
bool is_similar(vector<string>&, vector<string>&);
extern std::ifstream::pos_type filesize(const char* filename);

void convertMaster(string input_file_name) {
	vector<vector<string> > hypon_list;
	vector<vector<string> >::iterator iter1;		//To iterate through sets if hyponyms
	vector<string>::iterator iter2;				//To iterate through hyponyms
	string word = "test";
	int vector_size[2];
	char garbage;
	

	ifstream input(input_file_name.c_str());
	if (!input) {
		cout << "Code Hippo!";
		return;
	}


	//this gonna' get messy ;)
	//cout << "Filesize: " << filesize(input_file_name.c_str()) << endl;
	while (input.tellg() < filesize(input_file_name.c_str())){
		//cout << "You position is " << input.tellg() << " out of " << filesize(input_file_name.c_str()) << "\n";
		vector<string> tmp_vec;
		while (input.peek() != list_delim) {
			getline(input, word, '\n');
			tmp_vec.push_back(word);
			cout << "Word: " << word << endl;
			garbage = input.peek();
			//cout << "Pushed " << word << " into tmp_vec." << endl;
		}
		hypon_list.push_back(tmp_vec);
		//cout << "Pushed vector into vector.\n";
		getline(input, word, '\n');		//Collect the useless '-'
	}

	/* Display all vectors (uncomment)
	vector_size[0] = hypon_list.size();
	for (int i = 0; i < vector_size[0]; i++) {
		cout << "New vector: \n";
		vector_size[1] = hypon_list[i].size();
		for (int j = 0; j < vector_size[1]; j++) {
			cout << hypon_list[i][j] << endl;
		}
	}
	*/
	vector_size[0] = hypon_list.size();
	int i, j;
	for (i = 1; i < vector_size[0]; i++) {
		j = 0;
		while (j < i) {
			//cout << "Is " << hypon_list[i][0] << " similar to " << hypon_list[j][0] << ": " << is_similar(hypon_list[i], hypon_list[j]) << "\n";
			if (is_similar(hypon_list[i], hypon_list[j])) {
				hypon_list[i][0] = hypon_list[j][0];
				break;
			} else {
				j++;
			}
		}
	}
	
	ofstream output("finished_output.txt");
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
