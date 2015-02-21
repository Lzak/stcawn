/*
 * The following c++ code is part of a text categorization research project
 * directed by Dr. Sarah Zelikovitz.
 *
 * The intent of this portion of the project is to build on a given set of data
 * (specifically a list of words) by adding words to the list that bare distinct
 * similarities to the list, depending on what type of similarity we are testing.
 * (IE synonyms, hyponyms, etc...) This will be done by opening a program known as WordNet
 * from within our program to obtain the new words. The implementation of this code should
 * result in a strengthening of our known data set.
 *
 * Written by: Nuwan Panditaratne
 */

/*--------------------------------------------------------------------------------------------
                                       User Directions
 *When using the following .cpp file, one must be sure to include the following code files
  in an accessible directory: 
                            - "stemmerAlg.h" (To utilize the porter Stemmer algorithm)
			    - "researchFunctions.cpp" (To utilize non-member functions essential for 
                              program functionality

 *This code utilizes data files, that for ease of scalability, are represented by the following
  arguments and can be changed upon execution:
				   -argv[1] :known dataset1
				   
*You must also include a blank text file named outPutPipe.txt in an accessible directory

*This code can be executed from the Unix command prompt as follows (replacing arguments with the actual file names listed
 in the directory):
             a.out argv[1]

	     *argv1 is the stem for all text files used in the program
	     *all actual files are followed by f1.txt, f2.txt, f3.txt...

             ie
             a.out test

*When prompted to, you must enter a searchtype to retrieve particular information from wordNet:
**For a hyponym test, enter "-hypon -treen" when prompted to.             

---------------------------------------------------------------------------------------------*/        
                     
#include<iostream>
//#include"researchFunctions.cpp"
#include<fstream>
#include<string>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include<ctime>
#include <set>
#include<list>
#include<cstring>
#include <iomanip>


using namespace std;



void CallWordNet(char UnixCall[100]);
char* findNextWord(char* & y);
void parseRun1();
list<string> parseRun2(string input);
void stemWNOut(list<string> &  wordNetList);
list<string>  stemWNIn(list<string> & wordNetList);
void makingListOfWords(char[], char[], char[] );


int main(int argc, char * argv[])
{
  
 
 
    // declaration of variables
    bool match=false;
    list<char*> words;
    list<char*>::iterator wordIter;
    list<list<string> > wordNetList;
    list<list<string> >::iterator listIter;
    list<set<string> >stemWordNetList;
    list<set<string> >::iterator sWNLIter;
    wordIter=words.begin();
    listIter=wordNetList.begin();
    sWNLIter=stemWordNetList.begin();
    list<string> funcList;
	string tempString;
    list<string>::iterator funcListIter;
    list<string> stemFuncList;
    list<string>::iterator sFIter;
    set<string> sortedSet;
    set<string>::iterator ssIter;
    ssIter=sortedSet.begin();

    string temp;

    list<set<string> > cluster;
    list<set<string> >::iterator clusterIt;
    list<set<string> >::iterator loopIt;
    clusterIt=cluster.begin();
    loopIt=cluster.begin();
    list<set<string> > finalCluster;
    list<set<string> >::iterator finalIt;

    set<string>::iterator tempIt;
    set<string>::iterator tempIt2;
    set<string>::iterator fillIn;

    char input[100];
    int counter=0;
    int i=1;
    int j=1;

    //declaring components of the Unix Command meant to open WordNet
    char UnixCommand[100];
    char header[]="/usr/local/WordNet-3.0/bin/wn ";
    char wordNetWord[100];
    char searchType[100];
    char tempSearchType[100]; 
	ifstream inFile;
    /*char* mainStem=argv[1];
	
    //parses known dataset1 into a sorted list
    char * filename=mainStem;
    
    strcat(filename,"f1.txt"); //dataset1
   
    char * strippedFile=mainStem;
    strcat(strippedFile,"f7.txt"); //parsed file
  
     
   
    char * ds1List=mainStem;
    strcat(ds1List,"f3.txt");
	*/
	char * filename = "testf1.txt";
	char * strippedFile = "testf7.txt";
	char * ds1List = "testf3.txt";
    inFile.open(filename);

 
    //call this function to create a list of the words without the frequencies and without
	//the name of file and clas
    makingListOfWords(filename,strippedFile, ds1List);
 
    inFile.close();
    
    ofstream outFile;
    //char * ds1WNresults=mainStem;
    //strcat(ds1WNresults,"f4.txt");
	char * ds1WNresults = "testf4.txt";
    outFile.open("ds1WNout.txt");

    //allows end user to select "wordnet" searchtype 
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
    strcpy(tempSearchType, searchType);
   
    system("clear");
   
    
 
    ifstream inFile2;
    inFile2.open("testf3.txt"); //this is ds1List
    if(!inFile2)
      {
	cout<<"error";
	return 1;
      }
    //inserts all the words from the known data set into the list "words"
    cout<<"before while loop"<<endl;         
       while(!inFile2.eof()) //this is just a list of words
      {

	cout<<endl;
        cout<<":) "<<endl;
      
	inFile2>>input; //read the first word
	cout << "after first input: "<<input <<endl;
       
	// cout<<input;
	//cout<<endl<<input<<endl<<endl;
	//cout.flush();
	
	if(strlen(input)!=0) //is there a word
	  {
	words.insert(wordIter,input); //insert it into the list "words"
	    cout << "after first insert" <<endl;
	    counter++; //count it

	    strcpy(wordNetWord,input);//copy the word to wordNetWord
	    cout << "after strcpy"<<endl;


	    //forming the unix command from the gathered information
	   strcpy(UnixCommand,header);
	   strcat(searchType," >outPutPipe.txt");
	   strcat(UnixCommand,wordNetWord);
	   strcat(UnixCommand," ");
	   strcat(UnixCommand, searchType);
	   cout << "after setting unix command" << endl;
	    //cout<<UnixCommand<<endl;
	   //put this back!  just for debugging
	  // CallWordNet(UnixCommand);  //call wordNet on this word which just calls the system with the Unix call
	   cout << "after return from callwordnet"<<endl;
	   parseRun1();
           funcList=parseRun2(input);
	   wordNetList.insert(listIter, funcList);
	 

	  strcpy(searchType,tempSearchType);

	  for(funcListIter=funcList.begin();funcListIter!=funcList.end();++funcListIter)
	    {
		  tempString = *funcListIter;
	      outFile<<tempString<<' ';
	      sortedSet.insert(*funcListIter);
	    }
	  
	  stemWordNetList.insert(sWNLIter,sortedSet);
	  cluster.insert(clusterIt,sortedSet);
	  sortedSet.clear();


	  //      free(s);
	  outFile<<endl;
	  }
	else 
	  break;
       
	//end of while loop
    }
     inFile2.close();
     outFile.close();

     cout<<"passedLoops"<<endl;
    



     /*     
     i=1;
     j=1;
     //stemming the cluster
       
     char * clusterDS1=mainStem;
     strcat(clusterDS1,"f8.txt");
     char * stemmedDS1=mainStem;
     strcat(stemmedDS1,"f9.txt");
   

  

     ofstream clusterOutput;
     clusterOutput.open(clusterDS1);
     s = (char *) malloc(i_max+1);
       

     //places elements of cluster into a text file to be stemmed
     for(clusterIt=cluster.begin(); clusterIt!=cluster.end(); ++clusterIt)
       {
	 for(tempIt=(*clusterIt).begin(); tempIt!=(*clusterIt).end(); ++tempIt)
	   {
         
	     clusterOutput<<*tempIt<<' ';
	   }
	     clusterOutput<<"zzzzzz"<<endl;
       }

     clusterOutput.close();

     //stems text file
     ofstream stemFileDS1;
     stemFileDS1.open(stemmedDS1); 
     FILE * stemmer=fopen(clusterDS1,"r");
     stemfile(stemmer,stemFileDS1);
     stemFileDS1.close();

   
     ifstream postStemDS1;
     postStemDS1.open(stemmedDS1);

     list<list<string> > stemmedCluster1;
     list<list<string> >::iterator sc1;
     list<string> clusterComponent1;
     list<string>::iterator ccIter;
     string removeZ;


     ccIter=clusterComponent1.begin();
     sc1=stemmedCluster1.begin();

     //creates a cluster of the stemmed results of DS1
     while(!postStemDS1.eof())
       {
	 postStemDS1>>removeZ;
	 if(removeZ!="zzzzzz")
	   clusterComponent1.insert(ccIter,removeZ);
	 else
	   {
	     stemmedCluster1.insert(sc1,clusterComponent1);
	     clusterComponent1.clear();
	     ccIter=clusterComponent1.begin();
	   }

	   
       }


     */
    
     //******************* comparing document and  knowledge data set begins here

     cout<<"adding to group"<<endl;    
     
 //adds the first cluster to the final group of clusters
  for(clusterIt=cluster.begin(); clusterIt!=cluster.end(); ++clusterIt)
    {
     for(tempIt=(*clusterIt).begin(); tempIt!=(*clusterIt).end(); ++tempIt)
      {
      for(loopIt=cluster.begin(); loopIt!=cluster.end(); ++loopIt)
      {
      {
      for(tempIt2=(*loopIt).begin(); tempIt2!=(*loopIt).end(); ++tempIt2)
      {
	 if((*tempIt)==(*tempIt2))
          {
	  for(fillIn=(*clusterIt).begin(); fillIn!=(*clusterIt).end();++fillIn)
	   (*loopIt).insert(*fillIn);

	   break;
       }}}}}
       

       
   }

     
     clusterIt=cluster.begin();
     finalIt=finalCluster.begin();
     finalCluster.insert(finalIt,(*clusterIt));

     i=1;
     j=1;


     
    

     cout<<"combining clusters"<<endl;
     
     for(clusterIt=cluster.begin(); clusterIt!=cluster.end(); ++clusterIt)
     {
      tempIt=(*clusterIt).begin();
      finalIt=finalCluster.begin();
      for(finalIt=finalCluster.begin();finalIt!=finalCluster.end();++finalIt)
	{
          tempIt2=(*finalIt).begin();
	  if(*tempIt == *tempIt2)
	    {
	      match=false;
	      break;
	    }
	  else
	    {
	      j++;
	      match=true;
	    }
	}
      if(match)
	{
	  finalCluster.insert(finalIt,(*clusterIt));
	}

      j=1;
      }
     cout<<"complete final clusters"<<endl;









     /*
      ifstream data;
      data.open(filename);
      
      ofstream outData;
      char * ds1groupFreq=mainStem;
      strcat(ds1groupFreq,"f5.txt");
      outData.open(ds1groupFreq);

      // cout<<endl<<endl<<endl<<data.peek();

      while(!data.eof())
	{
	  data>>temp;
	  i=1;
          //returns group occurences in group enhanced dataset1
	  for(finalIt=finalCluster.begin();finalIt!=finalCluster.end();++finalIt)
	    {
	    match=false;
	    for(tempIt=(*finalIt).begin(); tempIt!=(*finalIt).end(); ++tempIt)
	    {
	      if(*tempIt==temp)
		{
		  outData<<i<<' ';
		  match=true;
		  break;
		}
	    }
	  
	    if(match==true)
	    break;
	    outData<<endl;
	    i++;
	    }
	}
      data.close();
      outData.close();

      ifstream testdata;
      char * filename2=mainStem;
      strcat(filename2,"f2.txt");
      testdata.open(filename2);

      ofstream testoutData;
      char * ds2groupFreq= mainStem;
      strcat(ds2groupFreq,"f6.txt");
      testoutData.open(ds2groupFreq);
     */ 
   
        return 0;
 }

