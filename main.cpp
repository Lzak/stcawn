/*
Title: Short Text Classification Accompanying WordNet
Directed By: Dr. Sarah Zelikovitz
Author: Lasha Zakariashvili

* The following c++ code is part of a text categorization research project
* directed by Dr. Sarah Zelikovitz.
* The intent of this portion of the project is to build on a given set of data
* (specifically a list of words) by adding words to the list that bare distinct
* similarities to the list, depending on what type of similarity we are testing.
* (IE synonyms, hyponyms, etc...) This will be done by opening a program known as WordNet
* from within our program to obtain the new words. The implementation of this code should
* result in a strengthening of our known data set.
*/


#include <iostream>
#include <string>
#include "porter2_stemmer.h"

using std::string;
using std::cout;

int main() {
	//Porter2Stemmer::stem(word);
	system("pause");
	return 0;
}

/*
cout<<"searchtype is at least one of the following:"<<endl;
cout<<"\t-ants{n|v|a|r}          Antonyms"<<endl;
cout<<"\t-hype{n|v}              Hypernyms"<<endl;
cout<<"\t-hypo{n|v}, -tree{n|v}  Hyponyms & Hyponym Tree"<<endl;
cout<<"\t-entav                  Verb Entailment"<<endl;
cout<<"\t-syns{n|v|a|r}          Synonyms (ordered by estimated frequency)"<<endl;
cout<<"\t-smemn                  Member of Holonyms"<<endl;
cout<<"\t-ssubn                  Substance of Holonyms"<<endl;
cout<<"\t-sprtn                  Part of Holonyms"<<endl;
cout<<"\t-membn                  Has Member Meronyms"<<endl;
cout<<"\t-subsn                  Has Substance Meronyms"<<endl;
cout<<"\t-partn                  Has Part Meronyms"<<endl;
cout<<"\t-meron                  All Meronyms"<<endl;
cout<<"\t-holon                  All Holonyms"<<endl;
cout<<"\t-causv                  Cause to"<<endl;
cout<<"\t-pert{a|r}              Pertainyms"<<endl;
cout<<"\t-attr{n|a}              Attributes"<<endl;
cout<<"\t-deri{n|v}              Derived Forms"<<endl;
cout<<"\t-domn{n|v|a|r}          Domain"<<endl;
cout<<"\t-domt{n|v|a|r}          Domain Terms"<<endl;
cout<<"\t-faml{n|v|a|r}          Familiarity & Polysemy Count"<<endl;
cout<<"\t-framv                  Verb Frames"<<endl;
cout<<"\t-coor{n|v}              Coordinate Terms (sisters)"<<endl;
cout<<"\t-simsv                  Synonyms (grouped by similarity of meaning)"<<endl;
cout<<"\t-hmern                  Hierarchical Meronyms"<<endl;
cout<<"\t-hholn                  Hierarchical Holonyms"<<endl;
cout<<"\t-grep{n|v|a|r}          List of Compound Words"<<endl;
cout<<"\t-over                   Overview of Senses"<<endl<<endl;

cout<<"Enter desired searchtype from list of commands: ";
cin.getline(searchType,100);

*/