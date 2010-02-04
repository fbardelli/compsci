// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 1 Part 2 #2
// September 9, 2009
//---------- SOURCE CODE BEGINS HERE ----------

#include <iostream>
#include <stdlib.h>
using namespace std;

// Set up an array mapping command names 
// to descriptions of the command.
const int NUM_COMMANDS = 10;
const string COMMANDS[NUM_COMMANDS][2] = {
    {"chmod","change file mode bits"},
    {"mv","move (rename) files"},
    {"cp","copy files and directories"},
    {"mkdir","make directories"},
    {"ls","list directory contents"},
    {"rm","remove files or directories"},
    {"pwd","print name of current/working directory"},
    {"touch","change file timestamps"},
    {"man","an interface to the on-line reference manuals"},
    {"cd","Change the current directory"}
};
 
int main(){
 string input = "";
 while (1){
    //Prompt the user for a command name
    cout << "Enter a Program Name: ";
    cin >> input;
    //if they entered "quit" exit the loop
    if(input.compare("quit") == 0){
      cout << "Quiting...\n";
      break;
    }
    string description = "";
    //scan the list of cammands looking for a match
    for(int i = 0; i < NUM_COMMANDS; i++){
      if( input.compare(COMMANDS[i][0]) == 0){
        description = COMMANDS[i][1];
        break;
      }
    }
    // if description is filled in we have a match
    // otherwise display an error.
    if ( description.length() > 0 ){
      cout << input << " -- " << description << endl;
    } else {
      cout << "Invalid command: " << input << endl;
    }

  }
  return 0;
}
