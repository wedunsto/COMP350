#include<iostream>
#include<string.h>
#include<pthread.h>
#include<fstream>
#include<vector>
using namespace std;
//Use string stream to get integers and add to vector
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
		char *token=strtok(temp," ");
		while(token!=NULL){
			fileValues.push_back(stoi(token));
			token=strtok(NULL," ");
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
	cout<<"\n"<<values.size()<<endl;
	return 0;
}
