/*
 *William Dunston
 *COMP 350: Operating Systems Section 1
 *September 10, 2020
 *2.cpp introduced us to the execvp() method, which is capable of running a different program 
 *than the parent process
 */

#include<iostream>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(){
  int forkResult=fork();//Creates a parent and child process
  if(forkResult==0){//If the fork returns to the child process
    char counter[] = "wc";//Create the execvp() input parameter for generic word count
    char* countPointer = strdup(counter);//Convert input parameter to recognizable char pointer
    char wordCounter[] = "-w";//Create the execvp() input parameter for word count specifically
    //Convert input parameter to recognizable char pointer
    char* wordCounterPointer = strdup(wordCounter);
    //Create the execvp() input parameter for the file to perform word count on
    char filePath[] = "./1.cpp";
    char* filePathPointer = strdup(filePath);//Convert input parameter to recognizable char pointer
    //Creates a NULL terminated array of character pointers for the execvp() method
    char *args[]={countPointer,wordCounterPointer,filePathPointer,NULL};

    //Stores the word count from execvp() method
    int wordCount=execvp(args[0],args);
    //Prints word count to the standard output
    //cout<<"The number of words in 1.cpp is: :";
    //cout<<wordCount<<endl;
  }
  else if(forkResult>0){//If the fork returns to the parent process
    cout<<"I am the parent"<<endl;
  }
  else{//If the fork() did not successfully create a child process
    cout<<"The child process was not created"<<endl;
  }
	
  return 0;
}
