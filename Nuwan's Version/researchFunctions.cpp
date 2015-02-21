#include<iostream>
#include"stemmerAlg.h"
#include<fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include<ctime>
#include <set>
#include<list>
#include<cstring>
#include <iomanip>

using namespace std;
 

static char * s;

#define INC 50
static int i_max = INC;

void increase_s()
{  i_max += INC;
 {  char * new_s = (char *) malloc(i_max+1);
 { int i; for (i = 0; i < i_max; i++) new_s[i] = s[i]; } /* copy across */
 free(s); s = new_s;
 }
}

#define LETTER(ch) (isupper(ch) || islower(ch))

static void stemfile(FILE * f, ofstream & stemmedWordList )
{
  while(true)
    {  int ch = getc(f);
    if (ch == EOF) return;
    if (LETTER(ch))
      {  int i = 0;
      while(true)
        {  if (i == i_max) increase_s();

        ch = tolower(ch); /* forces lower case */

        s[i] = ch; i++;
        ch = getc(f);
        if (!LETTER(ch)) { ungetc(ch,f); break; }
        }
      s[stem(s,0,i-1)+1] = 0;
      /* the previous line calls the stemmer and uses its result to
         zero-terminate the string in s */
      stemmedWordList<<s<<endl;
      //cout<<s;

      }
    else putchar(ch);
    }


}


int returnArrayPosition(set<string> & readInList, string x)
{
  set<string>::iterator funcIter;
  int count=0;
  for(funcIter=readInList.begin();funcIter!=readInList.end();++funcIter)
    {

      if(*funcIter==x)
        return count-1;
      count++;
    }

  return -1;

}



//the above functions used exclusively for the porter stemmer alg.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CallWordNet(char UnixCall[100])
{
  system(UnixCall);
}



//filters word net data to retrieve
void parseRun1()
{

  int counter =0;
  ifstream inData;
  ofstream outData;
  ifstream parse;
  string x;
  char y[100];
  char temp;
  //opening data files
  inData.open("outPutPipe.txt");
  
  if (inData.peek()!=-1)
    {
      outData.open("parse1.txt");
      if (!outData)
	cout << "Error opening parse1.txt";

      while(!inData.eof())
	{

	  getline(inData,x);

	  if(x=="Sense 1" || x=="Sense 2" || x=="Sense 3" || x=="Sense 4" ||
	     x=="Sense 5")
	    {
	      getline(inData,x);
		  counter = 0;
	     // while(x!="Sense 1" && x!="Sense 2" && x!="Sense 3" &&  x!="Sense 4" &&
		   // x!="Sense 5" && !inData.eof())
		  while (!inData.eof() && x != "")
		{

		 
		  getline(inData,x);
		outData<<x<<endl;


		}
	 	    }

	  counter++;
          if(counter==6)
	    break;

	}

      inData.close();
      outData.close();
      return;
    }
  else
    {
      inData.close();
      return;
    }

}

list<string> parseRun2(string input)
{
  list<string> insideFunc;
  list<string>::iterator inFunc;
  inFunc=insideFunc.begin();


  bool noSpace=true;
  int i;
  ifstream inData;
  string x;
  char y[1000];
  char j[1000];
  char temp;
  int k=0;
  insideFunc.insert(inFunc,input);
  inData.open("parse1.txt");
  if (!inData) cout << "error opening file"<<endl;
  if(inData.peek()!=-1)
    {
   


      getline(inData,x);
      cout<<'-';
      while(!inData.eof())
	{
	
	  inData>>temp>>temp;
	  inData.getline(y,100);

	  for(i=0; y[i]!='\0'; i++)
	    {
	      //cout<<y[i];
	      if(y[i]!=',' )
		{
			  
			//  if (!noSpace)
			  {j[k]=y[i];
			  
			  }
			 
		}
	      else
		{
		  j[k]='\0';
	      
		  insideFunc.insert(inFunc,j);
		  // for(k=-1;k<1000;k++)
		  //        j[k]='\0';
		  noSpace=true;
		  k=-1;
		}
	      if(y[i+1]=='\0')
		{
		  j[k+1]='\0';
	      
		  insideFunc.insert(inFunc,j);
		  k=-1;
		}

	      k++;

	    }

	}
      inData.close();
      return insideFunc;
    }

  else
    {
      inData.close();

      return insideFunc ;
    }
}


//filters the known data set into a list of words with no repeats into a data file
void makingListOfWords(char fileName[], char strippedFile[], char  ds1List[])
{

  set<string> setOfWords;
  set<string>::iterator sow;
  sow=setOfWords.begin();
  string temp;
  string x;
  string y;
  ifstream stripFile;
  stripFile.open("testf1.txt"); //should be fileName
  ofstream justWordsAndFreqs;
  //char * strippedFile=argv[7];
  justWordsAndFreqs.open("testf7.txt"); //should be strippedFile

  while(!stripFile.eof()) //this is testf1.txt
    {
      stripFile>>temp>>temp; //get the first part out that has the file class and name
      getline(stripFile,x); //then get the rest of the line
      justWordsAndFreqs<<x; //put the rest of the line out to testf7.txt
	  justWordsAndFreqs << endl; //put a new line to testf7.txt
    }

  //puts words into a set and a facts file
  //close the files
  stripFile.close();
  justWordsAndFreqs.close();
  ifstream stripFreq;
  stripFreq.open("testf7.txt"); //should use strippedFile
  //char * ds1Stripped= argv[3];
  ofstream justWords;
  justWords.open("testf3.txt"); //should be ds1List

  while(!stripFreq.eof())
    {
      stripFreq>>x;
   
      // justWords<<x<<endl;
      setOfWords.insert(sow,x); //insert the word into the set of words
      stripFreq>>y; //get the freq and remove it
    }

  for(sow=setOfWords.begin();sow!=setOfWords.end();++sow)
    {
      justWords<<*sow<<' ';
    }

  justWords.close();
  stripFreq.close();
}

