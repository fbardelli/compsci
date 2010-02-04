/* $Id$ */
// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 3 Part 2
// October 11, 2009
//---------- SOURCE CODE BEGINS HERE ----------
// include C and C++ headers

#include <stdlib.h>
#include <iostream>
#include <fstream>

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
    void addToContent(char next);
    char getNextChar();
    bool empty();
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
 * void Message::addToContent(string next)
 * Appends a single character to the end of the message
 */
void Message::addToContent(char next){
  content.append(1,next);
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
    char decrypt(char c);
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
 * char Caesar::decrypt(char c)
 * given an encrypted character restores the original charactert
 * (Example: 
 *   char c = 'A'; 
 *   char e,f; 
 *   caesar.setShift(3); 
 *   e = caesar.encrypt(c);//returns 'D'
 *   f = caesar.decrypt(e);//returns 'A'
 */
char Caesar::decrypt(char c){
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
  
  //subtract the shift from the character, remove the offset to bring chr into the 0-25 range 
  int change = ( ( (chr - shift) - alpha_offset) % 26);
  if (change < 0){
    change = change + 26;
  }
  char new_letter = static_cast<char>( change + alpha_offset  );
  return new_letter;
}

/**
 * class fileHandleChar
 * Class to enable passing of single characters to a file
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
 * class fileHandleString
 * Class to read strings from a file
 */

class fileHandleString{
  public:
    //Copy constructor.  Have to define this because otherwise the compiler will try
    // to create a default copy including the ifsteam object, which will fail
    fileHandleString( fileHandleString & f){}
    // Constructor/Destructor
    fileHandleString();
    ~fileHandleString();
    string getFromFile();
  private:
    ifstream infile;
};

fileHandleString::fileHandleString() {
    infile.open("output.txt",ios::in);
    if(infile.fail()){
       cout << "Error: failed to open output.txt for reading\n";
       exit(1);
    }
}

fileHandleString::~fileHandleString(){
    infile.close();
}

string fileHandleString::getFromFile(){
  string line,output;
  while (getline(infile, line)){
    output += line + "\n";
  }
  return output;
}

/**
 * class Encryption 
 * manages the task of writing an encrypted string to a file
 * and reading a decrypted string from a file.
 */
class Encryption {
  public:
    Encryption();
    void encryptThisString(string st, int shift);
    void decryptThis(int shift);
    void printDecrypted();
    string encode(char c);
    char decode(string s);
  private:
    Caesar caesar;
    Message message;
    Message decrypted;
    string alphabet;
};


Encryption::Encryption(){
  alphabet = "ABCDEFGHIJKLMNOP";
}

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
  int position = 0;
  while(! message.empty() ){
    char next = message.getNextChar();
    string encoded = encode(next);
    fh.passToFile(caesar.encrypt(encoded[0]));
    fh.passToFile(caesar.encrypt(encoded[1]));
    if( position++ % 2){
      fh.passToFile(' ');
    }
  }
}

void Encryption::decryptThis(int shift){
  fileHandleString fhs;
  message = Message(fhs.getFromFile());
  decrypted = Message();
  caesar = Caesar(shift);
  while(! message.empty()){
    char next = message.getNextChar();
    if( next != ' '){
      string encoded;
      encoded += caesar.decrypt(next);
      if(! message.empty()){
        encoded += caesar.decrypt(message.getNextChar());
        decrypted.addToContent(decode(encoded));
      }
    }
  }
}

void Encryption::printDecrypted(){
  decrypted.print();
}

char Encryption::decode(string s){
  int indexA = static_cast<int>('A');
  int highBit = (static_cast<int>(s[0])) - indexA;
  int lowBit  = (static_cast<int>(s[1])) - indexA;
  char original = static_cast<char>((highBit*16)+lowBit); 
  return original;
}

string Encryption::encode(char c){
  int chr = static_cast<int>(c);
  string encoded;
  encoded += alphabet[chr/16];
  encoded += alphabet[chr%16];
  return encoded;
}



int main(){
  int key;
  string message;
  string input;
  cout << "Enter E to encrypt or D to decrypt:";
  getline(cin,input);
  Encryption e = Encryption();
  if (input == "D" || input == "d"){
    cout << "Enter an encryption key:" << endl;
    if( cin >> key ){
      e.decryptThis(key); 
      e.printDecrypted();
      cout << endl;
    }else{
      cout << "invalid input. Exiting\n";
      exit(1); 
    }
  }else if (input == "E" || input == "e"){
    cout << "Enter a message:" << endl;
    getline(cin, message);
    cout << "Enter an encryption key:" << endl;
    if(  cin >> key ){
      e.encryptThisString(message, key);
    }else{
      cout << "invalid input. Exiting\n";
      exit(1); 
    }
  }else{
    cout << "invalid input:" << input << endl;
  }
}
