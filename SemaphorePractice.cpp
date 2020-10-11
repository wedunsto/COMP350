/*
 *Objective: Practice incrementing and decrementing
 *a semaphore
 */

#include<iostream>
#include<semaphore.h>
#include<pthread.h>
#include<vector>
using namespace std;

vector<int> bufferContainer;//Semaphore buffer
sem_t semaphore;//declare semaphore
pthread_mutex_t lock;//Create a mutex lock for sync

void *incrementSemaphore(void *args){//Increment semaphore and buffer size
	pthread_mutex_lock(&lock);
	sem_post(&semaphore);
	int bufferValue=*((int*)args);//Store the value to place into buffer
	bufferContainer.push_back(bufferValue);
	cout<<"The buffer size is now: "<<bufferContainer.size()<<endl;
	pthread_mutex_unlock(&lock);
	return NULL;
}

void *decrementSemaphore(void *args){
	pthread_mutex_lock(&lock);
	sem_wait(&semaphore);//Thread is blocked if semaphore==0
	bufferContainer.erase(bufferContainer.begin());
	cout<<"The buffer size is now: "<<bufferContainer.size()<<endl;
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(){
	int initLock=pthread_mutex_init(&lock,NULL);//Initialize lock
	int singleValue=8;
	sem_init(&semaphore,0,0);//Initialize semaphore at 0 private to this process
	pthread_t tid0;
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid0,NULL,incrementSemaphore,(void *)&singleValue);
	pthread_create(&tid1,NULL,incrementSemaphore,(void *)&singleValue);
	pthread_create(&tid2,NULL,decrementSemaphore,NULL);
	return 0;
}
