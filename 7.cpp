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
int bufferSize;//Store the size of the buffer
vector<int> bufferContainer;//Vector to serve as buffer
sem_t semaphore;//Data structure used to solve synchronization problems
pthread_mutex_t lock;//Used to protect critical section

void *incrementBuffer(void *args){
  if(bufferContainer.size()<bufferSize){
    sem_post(&semaphore);//Increment the semaphore
    pthread_mutex_lock(&lock);//Lock the critical section
    int bufferValue =*((int *)args);//Store buffer value from parameters
    bufferContainer.push_back(bufferValue);//Increment buffer size
    cout<<"The buffer size is now: "<<bufferContainer.size()<<endl;
  }
  else{//Display buffer is full
    cout<<"buffer is full"<<endl;
  }
  pthread_mutex_unlock(&lock);//Unlock the critical section
  return NULL;
}

void *decrementBuffer(void *args){
  pthread_mutex_lock(&lock);//Lock the critical section
  if(bufferContainer.size()>0){
    sem_wait(&semaphore);//Decrement the (semaphore>0)
    bufferContainer.erase(bufferContainer.begin());//Decrement buffer size
    cout<<"The buffer size is now: "<<bufferContainer.size()<<endl;
  }
  else{//Display buffer is empty
    cout<<"Buffer is empty"<<endl;
  }
  pthread_mutex_unlock(&lock);//Unlock the critical section
  return NULL;
}



//Main method accepts inputs from the command line
int main(int argc, char* argv[]){
  if(argc!=4){//Confirmat of command line inputs
    cout<<"Not enough arguments"<<endl;
    return 1;
  }
  int initLock=pthread_mutex_init(&lock,NULL);//Initialize mutex lock
  sem_init(&semaphore,0,0);//Initialize semaphore to 0 and private to this process
  producerThreadCount=atoi(argv[1]);//Store count of producer threads
  consumerThreadCount=atoi(argv[2]);//Store count of consumer threads
  bufferSize=atoi(argv[3]);//Store buffer size
  pthread_t producerThreads[producerThreadCount];
  pthread_t consumerThreads[consumerThreadCount];
  int inputBuffer=0;//Value to input into the buffer
  for(int i=0;i<producerThreadCount;i++){
    pthread_create(&producerThreads[i],NULL,&incrementBuffer,(void *)&inputBuffer);
  }
  for(int j=0;j<consumerThreadCount;j++){
    pthread_create(&consumerThreads[j],NULL,&decrementBuffer,NULL);
  }
  for(int i=0;i<producerThreadCount;i++){//Wait for all threads to execute
    pthread_join(producerThreads[i],NULL);
  }
  for(int i=0;i<consumerThreadCount;i++){//Wait for all threads to execute
    pthread_join(consumerThreads[i],NULL);
  }
  return 0;
}
