#include<iostream>
#include<string.h>
#include<pthread.h>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

void populateThreadArray(pthread_t *threads, int size){
	for(int i=0;i<size;i++){
		pthread_t thread;
		int *myID=(int *)thread;
		cout<<i<<" "<<*myID<<endl;
		threads[i]=thread;
	}
}

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
	if(argc!=3){
		cout<<"There are too many or too little arguments"<<endl;
		return 0;
	}
	pthread_t threads[atoi(argv[1])];
	populateThreadArray(threads,atoi(argv[1]));
	string inputFileName(argv[2]);
	vector<int> values;
	populateValuesVector(values,inputFileName);
	return 0;
}
