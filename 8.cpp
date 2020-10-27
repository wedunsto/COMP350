/*
 *William Dunston
 *COMP 350: Section 1
 *October 26, 2020
 *Program assignment 8: Allow subsequent readers. Exclude critical
 *section to individual writers
 */
#include<iostream>
#include<pthread.h>
#include<vector>
#include<semaphore.h>
using namespace std;

int value=0;//Arbitrary value to write to data structure
vector<int> bufferContainer;//Vector to serve as buffer
sem_t mutex;//Used to protect the shared counter
sem_t roomEmpty;//Used to categorical mutual exclusion
int reader=0;//Keep track of the number of readers
pthread_mutex_t lock;//Used to protect critical section

void *readerFunction(void *args){
  sem_wait(&mutex);//Protect the reader counter
  reader++;//Increment the number of reader threads
  if(reader==1){//The first reader thread locks the room
    sem_wait(&roomEmpty);
  }
  sem_post(&mutex);
  pthread_mutex_lock(&lock);//Lock the critical section
  cout<<"Read the value: "<<value<<endl;
  pthread_mutex_unlock(&lock);//Unlock the critical section
  sem_wait(&mutex);//Protect the reader counter
  reader--;//Reduce the number of reader threads
  if(reader==0){//The last reader thread unlocks the room
    sem_post(&roomEmpty);
  }
  sem_post(&mutex);
  return NULL;
}

void *writerFunction(void *args){
  sem_wait(&roomEmpty);//Make sure no one is in the room
  pthread_mutex_lock(&lock);//Lock the critical section
  bufferContainer.push_back(value);//Add value to data structure
  cout<<"Added: "<<value<<endl;
  pthread_mutex_unlock(&lock);//Unlock the critical section
  sem_post(&roomEmpty);//Signal empty room
  return NULL;
}

int main(){
  //1 if no thread in critical section 0 if not
  sem_init(&roomEmpty,0,1);
  sem_init(&mutex,0,1);
  int initLock=pthread_mutex_init(&lock,NULL);//Initialize mutex lock
  pthread_t writerThreads[3];//Array of writer threads
  pthread_t readerThreads[3];//Array of reader threads
  //Creates writer threads
  for(int i=0;i<3;i++){
    pthread_create(&writerThreads[i],NULL,writerFunction,NULL);
  }
  for(int i=0;i<3;i++){
    pthread_create(&readerThreads[i],NULL,readerFunction,NULL);
  }
  //Process waits for all threads to finish
  for(int i=0;i<3;i++){
    pthread_join(writerThreads[i],NULL);
  }
  for(int i=0;i<3;i++){
    pthread_join(readerThreads[i],NULL);
  }
  return 0;
}
