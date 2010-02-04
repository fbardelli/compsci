/* $Id$ */
// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 3
// September 24, 2009
//---------- SOURCE CODE BEGINS HERE ----------
// include C and C++ headers

#include <stdlib.h>
#include <iostream>
#include "Encryption.h"

using namespace std;

int main(){
  int key;
  string message;
  string input;
  cout << "Enter E to encrypt or D to decrypt:";
  getline(cin,input);
  Encryption e = Encryption();
  if (input == "D" || input == "d"){
    cout << "Enter an encryption key:" << endl;
    cin >> key;
    e.decryptThis(key); 
    e.printDecrypted();
    cout << endl;
  }else if (input == "E" || input == "e"){
    cout << "Enter a message:" << endl;
    getline(cin, message);
    cout << "Enter an encryption key:" << endl;
    cin >> key;
    e.encryptThisString(message, key);
  }else{
    cout << "invalid input:" << input;
  }
}
