/*
 *William Dunsto0n
 *COMP 350: Section 1
 *November 2, 2020
 *Programming assignment 9: Solving the dining philosophers problem
 */

#include<iostream>
#include<pthread.h>
#include<vector>
#include<semaphore.h>
using namespace std;

sem_t forks[5];//Enforces mutual exclusion to forks using semaphores
int philosopher=0;//Identifies current philosopher
pthread_t philosophers[5];//Threads representing all philosophers at the table
pthread_mutex_t lock;//Used to protect critical section
pthread_mutex_t temp;
string state[5]={"thinking","thinking","thinking","thinking","thinking"};

int leftFork(int philosopher){//Identifies fork left of philosopher
  return philosopher;
}

int rightFork(int philosopher){//Identifies fork right of philosopher
  return (philosopher+1)%5;//Circular rotation of philosophers
}

void startEating(int philosopher){//Determine if current philosopher can eat
  if(state[philosopher]=="hungry" & state[leftFork(philosopher)]!="eating"
  & state[rightFork(philosopher)]!="eating"){
    state[philosopher]="eating";//Transition philosopher from hungry to eating
    cout<<"Philosopher: "<<philosopher<<" is eating."<<endl;
    sem_post(&forks[philosopher]);
  }
}

void getFork(int philosopher){//Pick up forks for philosopher
  pthread_mutex_lock(&lock);//Lock the critical section
  state[philosopher]="hungry";//Transistion philosopher from thinking to hungry
  cout<<"Philosopher: "<<philosopher<<" is hungry."<<endl;
  startEating(philosopher);//Determine if current philosopher can eats
  pthread_mutex_unlock(&lock);//Unlock the critical section
  sem_wait(&forks[philosopher]);
}

void putFork(int philosopher){//Put down forks for philosopher
  pthread_mutex_lock(&lock);//Lock the critical section
  state[philosopher]="thinking";//Transition philosopher from eating to thinking
  cout<<"Philosopher: "<<philosopher<<" is thinking."<<endl;
  startEating(rightFork(philosopher));//Determine if right philosopher can eat
  startEating(leftFork(philosopher));//Determine if left philosopher can eat
  pthread_mutex_unlock(&lock);//Unlock the critical section
}

void* philosopherProcess(void* args){//Method where philosophers eat
  int philosopher=*((int*)args);//convert arguement to int
  getFork(philosopher);//Pick up left fork
  putFork(philosopher);//Pick up right fork
  return NULL;
}

int main(){
  int initLock=pthread_mutex_init(&lock,NULL);//Initialize mutex lock
  for(int i=0;i<5;i++){//Create fork semaphores
    sem_init(&forks[i],0,1);//Initialize semaphores to 1 and private to this process
  }
  for(int i=0;i<5;i++){
    pthread_create(&philosophers[i],NULL,philosopherProcess,(void*)&i);
  }
  for(int i=0;i<5;i++){
    pthread_join(philosophers[i],NULL);
  }
  return 0;
}
