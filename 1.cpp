/*
 *William Dunston
 *COMP 350: Section 1
 *September 1, 2020
 *Program assignment 1: Create child process from parent process
 */

#include<iostream>
#include<unistd.h>
using namespace std;

void forkAssignment(){//Function used to display desired results
  int forkResult=fork();//Stores the fork() results
  if(forkResult==0){//If the child process was created and returns to child
    cout<<"I am the child"<<endl;
  }
  else if(forkResult>0){//If the child process was created and returns to parent
    cout<<"I am the parent"<<endl;
  }
  else{//If the fork() did not successfully create a child process
    cout<<"The child process was not created"<<endl;
  }
}

int main(){
  forkAssignment();//Calls the forkAssignment(__ function
  return 0;
}