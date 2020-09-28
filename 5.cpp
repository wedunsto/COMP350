/*
 *William Dunston
 *COMP 350: Section 1
 *September 28, 2020
 *Program assignment 4: Perform math using a dynamic count
 *of threads
 */

#include<iostream>
#include<string.h>
#include<pthread.h>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

int slice=0;//Keep track of list sections
//https://www.geeksforgeeks.org/sum-array-using-pthreads/
void *printID(void *arg){
	cout<<pthread_self()<<"\n";
	pthread_exit(NULL);
	return NULL;
}

void *calculateThreadSums(void *arg){
	int threadSection=slice;
	return NULL;
}
//Function to add file integers to a vector
void populateValuesVector(vector<int> &fileValues, string fileName){
	ifstream readFile(fileName);
	string temp;
	while(getline(readFile,temp)){
		stringstream stringValues(temp);
		string words;
		while(stringValues>>words){
			fileValues.push_back(stoi(words));
		}
	}
}

//Main method accepts inputs from the command line
int main(int argc, char* argv[]){
	int numberOfThreads=atoi(argv[1]);//Stores the number of threads
	if(argc!=3){//Handles too many or too little arguments
		cout<<"There are too many or too little arguments"<<endl;
		return 0;
	}
	int finalSum=0;//Store the final sum of thread sums
	pthread_t threads[numberOfThreads];//Create an array of threads
	int threadSums[numberOfThreads];//Array to store the thread sums
	string inputFileName(argv[2]);//Gets the file name
	vector<int> values;//Create a vector to store the file values
	
	for(int i=0;i<numberOfThreads;i++){//Populate thread array
		pthread_create(&threads[i],NULL,printID,NULL);
	}
	populateValuesVector(values,inputFileName);//Add file values to vector
	return 0;
}
