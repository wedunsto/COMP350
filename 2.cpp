#include<iostream>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(){
	char counter[] = "wc";
  char* countPointer = strdup(counter);
	char wordCounter[] = "-w";
  char* wordCounterPointer = strdup(wordCounter);
  char filePath[] = "./1.cpp";
  char* filePathPointer = strdup(filePath);
  char *args[]={countPointer,wordCounterPointer,filePathPointer,NULL};
  int wordCount=execvp(args[0],args);
  cout<<"The number of words in 1.cpp is: "<<wordCount<<endl;
  return 0;
}