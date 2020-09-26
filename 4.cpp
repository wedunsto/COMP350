/*
 *William Dunston
 *COMP 350: Section 1
 *September 25, 2020
 *Program assignment 4: Print 0 to 10 on two threads
 */
#include<iostream>
#include<pthread.h>
using namespace std;

void *printNumbers(void *arg){//Print digits from 0 to 10
	for(int i=0;i<11;i++){
		cout<<i<<" ";
	}
	cout<<endl;
}
void createThreads(){
	pthread_t firstThreadID;//Create the first thread ID
	pthread_t secondThreadID;//Create the second thread ID
	pthread_create(&firstThreadID,NULL,printNumbers,NULL);//Assigns the function to the thread
	pthread_create(&secondThreadID,NULL,printNumbers,NULL);//Assigns the function to the thread
	pthread_exit(NULL);//Exit the current thread
}

int main(){
	createThreads();
	return 0;
}
