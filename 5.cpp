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
int start=0;
int increment=0;
int stop=0;
vector<int> values;//Create a vector to store the file values
pthread_mutex_t lock;//Create a mutex lock for synchronization
//https://www.geeksforgeeks.org/sum-array-using-pthreads/

void *calculateThreadSums(void *arg){
	//int threadSection=slice;
	pthread_mutex_lock(&lock);//Locks the critical section
	cout<<start<<" : "<<stop<<endl;
	pthread_mutex_unlock(&lock);//Unlock the critical section
	start+=increment+1;
	stop+=increment+1;
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
	if(argc!=3){//Handles too many or too little arguments
		cout<<"There are too many or too little arguments"<<endl;
		return 0;
	}
	int numberOfThreads=atoi(argv[1]);//Stores the number of threads
	int finalSum=0;//Store the final sum of thread sums
	if(pthread_mutex_init(&lock, NULL)!=0){
		cout<<"mutex failed"<<endl;
		return 1;
	}
	pthread_t threads[numberOfThreads];//Create an array of threads
	string inputFileName(argv[2]);//Gets the file name
	int threadSums[numberOfThreads];//Array to store the thread sums
	
	populateValuesVector(values,inputFileName);//Add file values to vector
	increment=(values.size()-1)/numberOfThreads;
	stop+=increment;
	for(int i=0;i<numberOfThreads;i++){//Populate thread array
		pthread_create(&threads[i],NULL,calculateThreadSums,NULL);
	}
	for(int j=0;j<numberOfThreads;j++){
		pthread_join(threads[j], NULL);
	}
	return 0;
}
