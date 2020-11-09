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

int count=5;//Identifies the number of philosophers
sem_t forks[5];//Enforces mutual exclusion to forks using semaphores
int philosopher=0;//Identifies current philosopher
sem_t footman;//Prevent philosopher deadlock and starvation
string state[5]={"thinking","thinking","thinking","thinking","thinking"};

int leftFork(int philosopher){//Identifies fork left of philosopher
  return philosopher;
}

int rightFork(int philosopher){//Identifies fork right of philosopher
  return (philosopher+1)%count;//Circular rotation of philosophers
}

void startEating(int philosopher){//Determine if current philosopher can eat
  if(state[philosopher]=="hungry" && state[leftFork(philosopher)]!="eating"
  && state[rightFork(philosopher)]!="eating"){
    state[philosopher]="eating";//Transition philosopher from hungry to eating
    sem_post(&forks[philosopher]);
  }
}

void getFork(int philosopher){//Pick up forks for philosopher
  sem_wait(&footman);
  state[philosopher]="hungry";//Transistion philosopher from thinking to hungry
  startEating(philosopher);//Determine if current philosopher can eats
  sem_post(&footman);
  sem_wait(&forks[philosopher]);
  //sem_wait(&forks[rightFork(philosopher)]);
  //sem_wait(&forks[leftFork(philosopher)]);
}

void putFork(int philosopher){//Put down forks for philosopher
  /*sem_post(&forks[rightFork(philosopher)]);
  sem_post(&forks[leftFork(philosopher)]);
  sem_post(&footman);*/
  sem_wait(&footman);
  state[philosopher]="thinking";//Transition philosopher from eating to thinking
  startEating(rightFork(philosopher));//Determine if right philosopher can eat
  startEating(leftFork(philosopher));//Determine if left philosopher can eat
  sem_post(&footman);
}

int main(){
  sem_init(&footman,0,4);//Initialize semaphore to 4 and private to this process
  for(int i=0;i<count;i++){//Create fork semaphores
    sem_init(&forks[i],0,1);//Initialize semaphores to 1 and private to this process
  }
  return 0;
}
