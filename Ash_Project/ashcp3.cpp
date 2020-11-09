/*
 *William Dunston
 * Michael De Long
 *COMP 350: Section 1
 *September 22, 2020
 *Checkpoint 1: Prompts the user for inputs and allows
 *The user to exit the shell
 */

#include<iostream>
#include<string.h>
using namespace std;

string prompt="ash>";//Keeps track of current directory

//Prompts the user for a command and stores the command
string getPrompt(){
  char command[100];//Utilize char array to store 99 character commands
  cout<<prompt;
  cin.getline(command,100);
  return command;
}

//Displays the exit prompt
void printExit(){
  cout<<"Exit William Dunston, Michael De Long."<<endl;
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
  int size=userCommand.length()-3;//Subtract 3 to account for "cd "
  bool correctCommand=correctChangeDirectory(userCommand);
  if(userCommand.length()<3){//Change to home directory
    prompt="ash>";
  }
  else if(correctCommand==false){
    cout<<"Command is invalid"<<endl;
  }
  else{//Change to specific directory
    string head=prompt.substr(0,prompt.length()-1);//Create head string
    string destination=userCommand.substr(3,size);//Create destination string
    string tail=">";//Create tail string
    prompt=head+(string)"/"+destination+tail;//Concatenate to build working directory
  }
}

void printWorkingDirectory(){//Print the current working directory
  cout<<"Working directory is: "<<prompt.substr(0,prompt.length()-1)<<endl;
}

void nonBuiltInCommand(string userCommand){//Execvp non built in user commands
  char command[]=userCommand;//Create the execvp() input parameter
  char* commandPointer=strdup(command);//Convert input parameter to recognizable char pointer
  //Create a NULL terminated array of character pointers for execvp
  char* args[]={commandPointer,NULL};
  //Execute non built in command
  execvp(args[0],args);
}

int main(){
  while(true){//Continuously displays the command prompt
    string userCommand=getPrompt();//Gets and stores the user's command
    if(userCommand.substr(0,4)=="exit"){//Tell the loop when to break
      printExit();
      break;
    }
    else if(userCommand.substr(0,2)=="cd"){//If change directory command entered
      changeDirectory(userCommand);
    }
    else if(userCommand.substr(0,4)=="path"){//If print working directory command entered
      printWorkingDirectory();
    }
    else{//Handle non  built in commands
      nonBuiltInCommand(userCommand);
    }
  }
}
