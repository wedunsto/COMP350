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
sem_t roomEmpty;//Used to categorical mutual exclusion
pthread_mutex_t lock;//Used to protect critical section

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
  int initLock=pthread_mutex_init(&lock,NULL);//Initialize mutex lock
  pthread_t writerThreads[3];//Array of writer threads
  //Creates writer threads
  for(int i=0;i<3;i++){
    pthread_create(&writerThreads[i],NULL,writerFunction,NULL);
  }
  //Process waits for all threads to finish
  for(int i=0;i<3;i++){
    pthread_join(writerThreads[i],NULL);
  }
  return 0;
}
