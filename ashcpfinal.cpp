/*
 *William Dunston
 *Michael De Long
 *COMP 350: Section 1
 *November 15, 2020
 *Final checkpoint: Commands can now be executed from batch files
 *This feature is determined at the execution time
 */
#include <bits/stdc++.h> 
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
using namespace std;

char environmentPath[]="ASH=/bin";//Create path variable
string prompt="ash";

void programErrors(){
  cout<<"An error has occurred"<<endl;
}

//Prompts the user for a command and stores the command
string getPrompt(){
  char command[100];//Utilize char array to store 99 character commands
  cout<<prompt<<"> ";
  cin.getline(command,100);
  return command;
}

//Displays the exit prompt
void printExit(){
  cout<<"Exit William Dunston, Michael De Long."<<endl;
  exit(0);
}

bool correctChangeDirectory(string userCommand){//Method to confirm command format
  int size=userCommand.length();
  bool result=true;
  for(int i=3;i<size;i++){
    if(userCommand[i]==' '){
      result=false;
    }
  }
  return result;
}
//Executed when change directory command is executed
void changeDirectory(string userCommand){
  string prefix="ash";//Store ash CLI prefix
  char destination[100];//Store the directory destination
  bool correctCommand=correctChangeDirectory(userCommand);
  if(userCommand==" "|userCommand.length()==0){//Change to home directory
    chdir("~");
    getcwd(destination,100);
  }
  else if(correctCommand==false){//Error detected in change directory
    programErrors();
  }
  else{//Change to a child directory
    chdir(userCommand.c_str());
    getcwd(destination,100);
  }
  prompt=prefix+string(destination);
}

//FIX ME
void changePath(){//Set empty path
  cout<<"Non-built in function are no longer available."<<endl;
  setenv("PATH"," ",1);//Prevent the use of non-built in functions
}

void changePath(string userCommand){//Set user specified path
  int pathPosition=0;//Keep track of path part
  setenv("PATH"," ",1);//Reset the path variable
  cout<<"Depending on your path, non-built in functions may be available."<<endl;
	stringstream paths(userCommand);
	string path;
	while(getline(paths, path,' ')){//Tokenize the string for paths by space
	  if(pathPosition==0){
		  setenv("PATH",path.c_str(),1);//The first part of the path becomes the value
		}
		else{
		  string newPath=getenv("PATH")+':'+path;//If more paths added, concatenate and append
	    setenv("PATH",newPath.c_str(),1);
		}
          pathPosition++;
	}
}

void nonBuiltInCommand(string userCommand){//Execvp non built in user commands
  //Convert command into execvp format
  char* commandPointer=new char[userCommand.length()+1];
  strcpy(commandPointer,userCommand.c_str());
  //Create a NULL terminated array of character pointers for execvp
  char* args[]={commandPointer,NULL};
  //Execute non built in command
  execvp(args[0],args);
}

void readFromBatchFile(string fileName){
  fstream batchFile;
  batchFile.open(fileName);
  string userCommand;
  while(getline(batchFile,userCommand)){
    if(userCommand.substr(0,4)=="exit"){//Tell the loop when to break
      printExit();
    }
    else if(userCommand.substr(0,2)=="cd"){//If change directory command entered
      changeDirectory(userCommand);
    }
    else if(userCommand.substr(0,4)=="path"){//Change the search path
      if(userCommand.length()==4){
        changePath();
      }
      else{
        changePath(userCommand.substr(5));
      }
    }
    else{//Handle non  built in commands
      nonBuiltInCommand(userCommand);
    }
  }
  printExit();//Exit when the end of the file is reached
 }

int main(int argc, char* argv[]){
  putenv(environmentPath);//Initialize path to /bin
  if(argc==2){//Read commands from batch files
	string fileName=argv[1];//Get file name from command line
	cout<<"Reading commands from batch file: "<<fileName<<endl;
	readFromBatchFile(fileName);
  }
  else if(argc==1){//Interactive mode
    while(true){//Continuously displays the command prompt
      string userCommand=getPrompt();//Gets and stores the user's command
      if(userCommand.substr(0,4)=="exit"){//Tell the loop when to break
        printExit();
        break;
      }
      else if(userCommand.substr(0,2)=="cd"){//If change directory command entered
       changeDirectory(userCommand.substr(3));
      }
      else if(userCommand.substr(0,4)=="path"){//Change the search path
        if(userCommand.length()==4){
          changePath();
        }
        else{
          changePath(userCommand.substr(5));
        }
      }
      else{//Handle non  built in commands
        nonBuiltInCommand(userCommand);
      }
    }
  }
  else{
    programErrors();
  }
}
