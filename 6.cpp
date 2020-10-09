/*
 *William Dunston
 *COMP 350: Section 1
 *October 9, 2020
 *Program assignment 6: Utilize semaphores to increment
 *and decrement an unbound buffer
 */

#include<iostream>
#include<pthread.h>
#include<vector>
#include<semaphore.h>
using namespace std;

int producerThreadCount;//Store the number of producer threads
int consumerThreadCount;//Store the number of consumer threads

void *testMethod(void *args){
	cout<<"Hello World"<<endl;
	return NULL;
}

//Main method accepts inputs from the command line
int main(int argc, char* argv[]){
	producerThreadCount=atoi(argv[1]);//Store count of producer threads
	consumerThreadCount=atoi(argv[2]);//Store count of consumer threads
	pthread_t producerThreads[producerThreadCount];
	pthread_t consumerThreads[consumerThreadCount];
	for(int i=0;i<producerThreadCount;i++){
		pthread_create(&producerThreads[i],NULL,testMethod,NULL);
	}
	for(int j=0;j<consumerThreadCount;j++){
		pthread_create(&consumerThreads[j],NULL,testMethod,NULL);
	}
	return 0;
}
