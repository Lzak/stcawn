#include<iostream>
#include<list>
#include<string>
#include<iomanip>

using namespace std;


//structure representation of partitions and it's stored components
struct partitions{
  int partitionSize[4];
  int partitionWaste[4];
  int overallWaste;
  string partitionStatus[4];
  string currentJob[4];

  //partitions for external fragmentation
  string currentDynamicJob1[4];
  string currentDynamicJob2[4];
  
};


//structure representation of a list of jobs, including name and size of each job
struct job{
  list<string> jobNames;
  list<int> jobSize;
  list<string> statusOfJob; //running or waiting
};



class Algorithms
{

 public:
  
  void initializePartitionSize();
  void jobInitializations();
  void usingAlgorithm(char Alg);
  void print();
  
 private:
  partitions jobAllocations;
  job jobList;
  

};



//prompts user to enter sizes of partitions 1-4
void Algorithms::initializePartitionSize()
{

  int parValue;

  system("clear");
  cout<<"Please Enter an Interger Value for memory partitions 1-4: "<<endl;

  for(int i=0; i<4; i++)
    {
      cout<<"Partition #"<<i+1<<" : ";
      cin>>parValue;
      jobAllocations.partitionSize[i]=parValue;

      //sets initial usage status to free
      jobAllocations.partitionStatus[i]="free";
      jobAllocations.partitionWaste[i]=0;
      jobAllocations.currentDynamicJob1[i]=" ";
      jobAllocations.currentDynamicJob2[i]=" ";
    }

  jobAllocations.overallWaste=0;
  
}


//prompts user to enter job sizes and names
void Algorithms::jobInitializations()
{
  list<string>::iterator nameIT;
  list<int>::iterator sizeIT;
  nameIT=jobList.jobNames.begin();
  sizeIT=jobList.jobSize.begin();

  string name;
  int size;

  bool notF=false;


  system("clear");
  

  //user can enter f to end initializing job list
  while (!notF)
    {
      cout<<"Please enter a three character Job name followed by an ENTER. Type in "<<endl;
      cout<<"F if there are no more jobs to be executed: ";
      cin>>name;

      if(name !="f")
	{

	  jobList.jobNames.insert(nameIT,name);
	  cout<<endl<<"What is the integer size of "<<name<<"? : ";
	  cin>>size;
	  jobList.jobSize.insert(sizeIT,size);
	  cout<<endl<<endl;

	}

      else
	{
	  notF=true;
	}
    }
}


//uses a switch statement to choose an algorithm to run through user entered data
void Algorithms::usingAlgorithm(char Alg)
{
  list<string>::iterator nameIT;
  list<int>::iterator sizeIT;
  list<string>::iterator statusIT;
  list<int> nextInt;

  int k;
  nameIT=jobList.jobNames.begin();
  statusIT=jobList.statusOfJob.begin();
  list<int>::iterator nextIT;
  nextIT=nextInt.begin();
  

  bool stillUsable[4]={true,true,true,true};
  bool running=false;
  int bestPartition;
  int min=0;
  int next = 0;
  int counter =0;
  int tempWaste[4];
  int tempArray[4]={-1,-1,-1,-1};
  
  
  switch (Alg){
    //case f or F run the First Feed Algorithm 
  case 'f':
  case 'F':
    

    //job is placed in first available 
    for(sizeIT=jobList.jobSize.begin(); sizeIT!=jobList.jobSize.end();++sizeIT)
      {
	
	for(int i=0; i<4; i++)
	  {
	    if(*sizeIT <= jobAllocations.partitionSize[i] && 
	       jobAllocations.partitionStatus[i]!="BUSY")
	      {
		jobAllocations.currentJob[i]=(*nameIT);
		jobAllocations.partitionStatus[i]="BUSY";
		jobAllocations.partitionWaste[i]=jobAllocations.partitionSize[i]-
		  (*sizeIT);
		jobAllocations.overallWaste+=jobAllocations.partitionWaste[i];
		
		break;
		
	      }
	  }
	++nameIT;
      }



    //monitors waste
    for( int j=0; j<4; j++)
      {
	if(jobAllocations.partitionStatus[j]=="free")
	  {
	    jobAllocations.partitionWaste[j]=jobAllocations.partitionSize[j];
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[j];
	  }
      }
    

    //judges status of jobs
    for(nameIT=jobList.jobNames.begin(); nameIT!=jobList.jobNames.end(); ++nameIT)
      {
	running=false;

	for( int k=0; k<4; k++)
	  {
	    if(jobAllocations.currentJob[k]==*nameIT && 
	       jobAllocations.partitionStatus[k]=="BUSY")
	      {
		jobList.statusOfJob.insert(statusIT,"RUNNING");
		running=true;
	      }

	  }
	if(!running)
	  jobList.statusOfJob.insert(statusIT,"WAITING");


	
      }
      
    
    break;


    //algorithm for Next Fit
  case 'n':
  case 'N':
    
    //job is placed in first available, however the first recursion of the for loops
    //begin after the most recently used partition 
    for(sizeIT=jobList.jobSize.begin(); sizeIT!=jobList.jobSize.end();++sizeIT)
      {
	counter=0;
	

	//the next variable points to the partition after the most recently
	//used partition

	//much like the first feed algorithm
	for(int i=next; i<4; i++)
	  {

	    if(counter==12)
	      break;

	    if(next==3)
	      next=0;

	    //updates state of partition
	    if(*sizeIT <= jobAllocations.partitionSize[i] && 
	       jobAllocations.partitionStatus[i]!="BUSY")
	      {
		jobAllocations.currentJob[i]=(*nameIT);
		jobAllocations.partitionStatus[i]="BUSY";
		jobAllocations.partitionWaste[i]=jobAllocations.partitionSize[i]-
		  (*sizeIT);
		jobAllocations.overallWaste+=jobAllocations.partitionWaste[i];
		next=i;

		break;
		
	      }
	    counter++;
	  }
	++nameIT;
      }


    --sizeIT;
    --nameIT;
    
    //fills in remaining job(s) into partition
    for(int i=0; i<4; i++)
      {
	if(*sizeIT <= jobAllocations.partitionSize[i] && 
	   jobAllocations.partitionStatus[i]!="BUSY")
	  {
	    jobAllocations.currentJob[i]=(*nameIT);
	    jobAllocations.partitionStatus[i]="BUSY";
	    jobAllocations.partitionWaste[i]=jobAllocations.partitionSize[i]-
	      (*sizeIT);
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[i];
	    
	    break;
	    
	  }
      }
    
    
    
    //monitors waste

    for( int j=0; j<4; j++)
      {
	if(jobAllocations.partitionStatus[j]=="free")
	  {
	    jobAllocations.partitionWaste[j]=jobAllocations.partitionSize[j];
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[j];
	  }
      }
    

    //judges status of jobs
    for(nameIT=jobList.jobNames.begin(); nameIT!=jobList.jobNames.end(); ++nameIT)
      {
	running=false;

	for( int k=0; k<4; k++)
	  {
	    if(jobAllocations.currentJob[k]==*nameIT && 
	       jobAllocations.partitionStatus[k]=="BUSY")
	      {
		jobList.statusOfJob.insert(statusIT,"RUNNING");
		running=true;
	      }

	  }

	if(!running)
	  jobList.statusOfJob.insert(statusIT,"WAITING");


	
      }
      

    break;
    

    //algorithm for best fit
  case 'b':
  case 'B':


    for(sizeIT=jobList.jobSize.begin(); sizeIT!=jobList.jobSize.end();++sizeIT)
      {
	
	bestPartition=-1;

	//attempts to find the partition with the smallest waste
	for(k=0; k<4; k++)
	  {
	    if(jobAllocations.partitionStatus[k]!="BUSY")
	      {
		tempWaste[k]= jobAllocations.partitionSize[k]-*sizeIT;
		if(tempWaste[k]<0)
		  tempWaste[k]=-1;
	      }
	    else
	      tempWaste[k]=-1;
	    
	  }

	min=0;
	for(k=0;k<4;k++)
	  {
	    if(tempWaste[k]!=-1 && 
	       jobAllocations.partitionStatus[k]!="BUSY")
	      {
		tempArray[min]=tempWaste[k];
		min++;
	      }
	    

	  }
	
	min=tempArray[0];
	for(k=0;k<4 && tempArray[k]!=-1;k++)
	  {
	    if(tempArray[k]<=min && min != -1 )
	      {
		min=tempArray[k];
		
	      }
	  }


	for(k=0;k<4;k++)
	  {
	    if(tempWaste[k]==min
	       && jobAllocations.partitionStatus[k] !="BUSY")
	      {
		bestPartition=k;
		break;
	      }
	  }
	 
	if(bestPartition>-1)
	  {
	    
	    jobAllocations.currentJob[bestPartition]=*nameIT;
	    jobAllocations.partitionStatus[bestPartition]="BUSY";
	    jobAllocations.partitionWaste[bestPartition]=jobAllocations.partitionSize[bestPartition]-
	      (*sizeIT);
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[bestPartition];
	  }
	 
	++nameIT;
	
      }

    --sizeIT;
    --nameIT;
    

    //fills in remaining job in available partition
    for(int i=0; i<4; i++)
      {
	if(*sizeIT <= jobAllocations.partitionSize[i] && 
	   jobAllocations.partitionStatus[i]!="BUSY")
	  {
	    jobAllocations.currentJob[i]=(*nameIT);
	    jobAllocations.partitionStatus[i]="BUSY";
	    jobAllocations.partitionWaste[i]=jobAllocations.partitionSize[i]-
	      (*sizeIT);
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[i];
	    
	    break;
	    
	  }
      }
    //monitors waste
    for( int j=0; j<4; j++)
      {
	if(jobAllocations.partitionStatus[j]=="free")
	  {
	    jobAllocations.partitionWaste[j]=jobAllocations.partitionSize[j];
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[j];
	  }
      }
    
    //judges status of jobs
    for(nameIT=jobList.jobNames.begin(); nameIT!=jobList.jobNames.end(); ++nameIT)
      {
	running=false;

	for( int k=0; k<4; k++)
	  {
	    if(jobAllocations.currentJob[k]==*nameIT && 
	       jobAllocations.partitionStatus[k]=="BUSY")
	      {
		jobList.statusOfJob.insert(statusIT,"RUNNING");
		running=true;
	      }

	  }

	if(!running)
	  jobList.statusOfJob.insert(statusIT,"WAITING");
	
      }
      
    
    
    break;

    //algorithm for worst fit
  case 'w':
  case 'W':
    
    for(sizeIT=jobList.jobSize.begin(); sizeIT!=jobList.jobSize.end();++sizeIT)
      {
	
	bestPartition=-1;

	//attempts to find the partition with the largest waste
	for(k=0; k<4; k++)
	  {
	    if(stillUsable[k]=true && 
	       jobAllocations.partitionStatus[k]!="BUSY")
	      {
		tempWaste[k]= jobAllocations.partitionSize[k]-*sizeIT;
		if(tempWaste[k]<0)
		  {
		    tempWaste[k]=-1;
		    stillUsable[k]=false;
		  }
	      }
	    else
	      tempWaste[k]=-1;
	    
	    
	  }


	//searches for suitable paritions
	min=0;
	for(k=0;k<4;k++)
	  {
	    if(tempWaste[k]!=-1 && jobAllocations.partitionStatus[k]!="BUSY")
	      {
		tempArray[min]=tempWaste[k];
		min++;
	      }
	    

	  }
	
	//finds partition with largest waste
	min=tempArray[0];
	for(k=0;k<4 && tempArray[k]!=-1;k++)
	  {
	    if(tempArray[k]>=min && min != -1 &&
	       jobAllocations.partitionStatus[k]!="BUSY")
	      {
		min=tempArray[k];
		
	      }
	  }


	//locates correct partition
	for(k=0;k<4;k++)
	  {
	    if(tempWaste[k]==min)
	      {
		bestPartition=k;
		break;
	      }
	  }
	 

	//updates state of partition
	if(bestPartition>-1)
	  {
	    jobAllocations.partitionStatus[bestPartition]="BUSY";
	    jobAllocations.partitionWaste[bestPartition]=jobAllocations.partitionSize[bestPartition]-
	      (*sizeIT);
	    jobAllocations.partitionSize[bestPartition]=jobAllocations.partitionWaste[bestPartition];
	    if(jobAllocations.partitionSize[bestPartition]>0)
	      stillUsable[bestPartition]=true;
	    else
	      stillUsable[bestPartition]=false;
	    
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[bestPartition];
	    
	    
	    jobAllocations.currentJob[bestPartition]=*nameIT;
	    
	    
	  }
	 
	++nameIT;
	
      }


    --nameIT;
    --sizeIT;

    //dynamically allocating jobs in remaining portion of partition
    for(int i=0; i<4; i++)
      {
	if(*sizeIT <= jobAllocations.partitionSize[i] && 
	   jobAllocations.partitionStatus[i]=="BUSY")
	  {
	    
	    jobAllocations.partitionSize[i]-=
	      (*sizeIT);
	    
	    if(jobAllocations.currentDynamicJob1[i]==" ")
	      jobAllocations.currentDynamicJob1[i]=*nameIT;
	    else
	      jobAllocations.currentDynamicJob2[i]=*nameIT;


	    
	    break;
	    
	  }
      }
    



    //monitors waste
    for( int j=0; j<4; j++)
      {
	if(jobAllocations.partitionStatus[j]=="free")
	  {
	    jobAllocations.partitionWaste[j]=jobAllocations.partitionSize[j];
	    jobAllocations.overallWaste+=jobAllocations.partitionWaste[j];
	  }
      }

    for( int j=0; j<4; j++)
      {
	if(jobAllocations.partitionStatus[j]=="BUSY")
	  {
	    jobAllocations.partitionWaste[j]=jobAllocations.partitionSize[j];
	  }
      }
    

    //judges status of jobs
    for(nameIT=jobList.jobNames.begin(); nameIT!=jobList.jobNames.end(); ++nameIT)
      {
	running=false;

	for( int k=0; k<4; k++)
	  {
	    if(jobAllocations.partitionStatus[k]=="BUSY")
	      {
		jobList.statusOfJob.insert(statusIT,"RUNNING");
		running=true;
		break;
	      }

	  }

	if(!running)
	  jobList.statusOfJob.insert(statusIT,"WAITING");
	
      }
      

    
    break;

  default:
    break;
  } 
}


void Algorithms::print()
{
  
  list<string>::iterator nameIT;
  list<int>::iterator sizeIT;
  list<string>::iterator statusIT;

  statusIT=jobList.statusOfJob.begin();
  
  //system("clear");
  cout<<"Job Name\t|Job Size\t|Located In Partition #"<<endl;
  cout<<"*****************************************************************************"<<endl;

  for(nameIT=jobList.jobNames.begin(),sizeIT=jobList.jobSize.begin();
      nameIT!=jobList.jobNames.end() && sizeIT != jobList.jobSize.end();
      ++nameIT, ++sizeIT, ++statusIT )
    {
      //if(sizeIT != jobList.jobSize.end() && statusIT!=jobList.statusOfJob.end())
      cout<<(*nameIT)<<"\t\t|\t"<<(*sizeIT)<<"\t|\t"<<(*statusIT)<<"\t|\t";
      
      for(int i=0; i<4; i++)
	{
	  if(jobAllocations.currentJob[i]==*nameIT)
	    {
	      cout<<"Partition "<<i+1<<" ";
	      //break;
	    }

	  
	}
      cout<<endl;
    }


  cout<<endl<<endl<<endl;

  cout<<"Part. #\t\t|Part. SIZE\t|Part. Status\t|Current JOB(S)\t|Part. Waste"<<endl;
  cout<<"*****************************************************************************"<<endl;
  
  for(int i=0; i<4; i++)
    {
      cout<<i+1<<"\t\t"<<jobAllocations.partitionSize[i]<<"\t\t"<<
	jobAllocations.partitionStatus[i]<<"\t\t"<<jobAllocations.currentJob[i]<<" ";

      //if dynamic partitions were used...jobs will be printed out
      if(jobAllocations.currentDynamicJob1[i]!=" ")
	cout<<jobAllocations.currentDynamicJob1[i]<<" ";


      
      if(jobAllocations.currentDynamicJob2[i]!=" ")
	cout<<jobAllocations.currentDynamicJob2[i]<<" ";

      cout<<"\t\t"<<jobAllocations.partitionWaste[i]<<endl;
    }

  cout<<endl<<endl;
  cout<<"The overall waste from using this method was : "<<jobAllocations.overallWaste;
  cout<<endl<<endl;


}




