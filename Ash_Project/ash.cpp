/*
 *William Dunston
 * Michael De Long
 *COMP 350: Section 1
 *September 22, 2020
 *Checkpoint 1: Prompts the user for inputs and allows
 *The user to exit the shell
 */

#include<iostream>
using namespace std;

//Prompts the user for a command and stores the command
string getPrompt(){
  char command[100];//Utilize char array to store 99 character commands
  cout<<"ash>";
  cin.getline(command,100);
  return command;
}

//Displays the exit prompt
void printExit(){
  cout<<"Exit William Dunston, Michael De Long."<<endl;
}

int main(){
  while(true){//Continuously displays the command prompt
    string userCommand=getPrompt();//Gets and stores the user's command
    if(userCommand=="exit"){//Tell the loop when to break
      printExit();
      break;
    }
  }
}