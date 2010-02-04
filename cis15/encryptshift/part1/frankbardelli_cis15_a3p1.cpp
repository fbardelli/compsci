/* $Id: /cis15/encryptshift/part1/encrypt.cpp 62 2009-10-09T14:34:29.877218Z frank  $ */
// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 3
// October 8, 2009
//---------- SOURCE CODE BEGINS HERE ----------
// include C and C++ headers

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

/**
 * class Message
 * provides access to a string 
 * as a stream of characters
 */
class Message {
  public:
    //Constructors
    Message() : content(""), location(0) {}
    Message(string new_content):content(new_content), location(0){}
    //Methods
    void print() const;
    void addToContent(string next);
    char getNextChar();
    bool empty();
    void main();
  private:
    string content;
    int location;
};

/**
 * void Message::print()
 * prints contents of the message
 */
void Message::print() const{
  cout << content;
}

/**
 * void Message::addToContent(string next)
 * Appends the string next to the end of the message
 */
void Message::addToContent(string next){
  content.append(next);
}

/**
 * char Message::getNextChar()
 * Returns the next character in the message
 */
char Message::getNextChar(){
  return content[location++];
}

/**
 * bool Message::empty()
 * Returns true when we've reached the end of the Message's content
 */
bool Message::empty(){
  return(content[location] == '\0');
}

/**
 * class Caesar
 * provides access to a simple
 * method of encryption
 */
class Caesar {
  public:
    //Constructors
    Caesar(){}
    Caesar(int s): shift(s){}
    //Methods
    void setShift(int s);
    char encrypt(char c);
  private:
    int shift;
};

/**
 * void Caesar::setShift(int s)
 * Sets a value for the number of characters we want to shift
 */
void Caesar::setShift(int s){
  shift = s;
}

/**
 * char Caesar::encrypt(char c)
 * given a character increments it by the offset stored in shift
 * (Example: 
 *   char c = 'A'; 
 *   caesar.setShift(3); 
 *   c = caesar.encrypt(c);//returns 'D'
 */
char Caesar::encrypt(char c){
  int chr = static_cast<int>(c);
  int alpha_offset;
  //need an offset so the modulus operation will work
  if (islower(c)){
    alpha_offset = static_cast<int>('a');
  }else if ( isupper(c)){
    alpha_offset = static_cast<int>('A');
  } else {
    //return non-alpha characters
    return c;  
  }
  //Add the shift to the character, remove the offset to bring chr into the 0-25 range 
  char new_letter = static_cast<char>( ( ( (chr + shift) - alpha_offset) % 26) + alpha_offset  );
  return new_letter;
}

/**
 * class fileHandleChar
 * provides access to a simple
 * method of encryption
 */
class fileHandleChar{
  public:
    //Copy constructor.  Have to define this because otherwise the compiler will try
    // to create a default copy including the ofsteam object, which will fail
    fileHandleChar( fileHandleChar & f){}
    // Constructor/Destructor
    fileHandleChar() : outfile("output.txt",ios::app){}
    ~fileHandleChar(){outfile.close();}
    //Methods
    void passToFile(char c);
  private:
    ofstream outfile;
};

/**
 * void fileHandleChar::passToFile(char c)
 * passes a character to the output file
 */
void fileHandleChar::passToFile(char c) {
  outfile << c;
}

/**
 * class Encryption 
 * manages the task of writing an encrypted string to a file
 */
class Encryption {
  public:
    void encryptThisString(string st, int shift);
  private:
    Caesar caesar;
    Message message;
};

/**
 * void Encryption::encryptThisString(string st, int shift)
 *   given a plaintext string and a shift value, initializes 
 *   a Caesar object with that shift value and writes the encrypted
 *   string to a file with fileHandleChar
 */
void Encryption::encryptThisString(string st, int shift){
  message = Message(st);
  caesar = Caesar(shift);
  fileHandleChar fh;
  while(! message.empty() ){
    fh.passToFile(caesar.encrypt(message.getNextChar()));
  }
}

int main(){
  int key;
  string message;
  cout << "Enter a message:" << endl;
  getline(cin, message);
  cout << "Enter an encryption key:" << endl;
  if(  cin >> key ){
    Encryption e = Encryption();
    e.encryptThisString(message, key);
  } else {
    cout << "invalid input. Exiting\n";
    exit(1); 
  }
}
