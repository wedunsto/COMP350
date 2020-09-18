#include<iostream>
#include<unistd.h>
#include<string.h>
using namespace std;

//Method to append user information to args array
void addToArray(char *array[], char *value, int currentIndex, int size){
	if(!(currentIndex>size)){
		array[currentIndex]=value;
	}
}

void createParentChild(){
	int SIZE=100;//Create a static size for the arrays
	char commandsAndArguments[SIZE];//Hold 99 characters
	char *args[SIZE];//Create args array for execvp()
	int pipe[2];//Write to [1] read from [0]
	int forkProcess=fork();//Forks the parent and child process
	if(forkProcess==0){//If the child process was created and returned to the child
		
		read(pipe[0],args,SIZE);//Read from pipe
		execvp(args[0],args);//Run user command
	}
	else if(forkProcess>0){
		cout<<"Please enter commands and arguments"<<endl;//Prompt for user input
		cin.getline(commandsAndArguments,SIZE);//Store user input
		char *temp=strtok(commandsAndArguments," ");//Tokenizer variable for user input
		int index=0;//Indexer for execvp() args array
		while(temp!=NULL){//Traverse user input
			addToArray(args,temp,index,SIZE);//Add value to execvp() arguments
			index++;//Increment array indexer
			temp=strtok(NULL," ");
		}
		write(pipe[1],args,SIZE);//Write to pipe
	}
	else{//If fork did not successfully create a child process
		cout<<"The child process was not created"<<endl;
	}
}

int main(){
	createParentChild();
	return 0;
}
