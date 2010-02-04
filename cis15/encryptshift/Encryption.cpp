/* $Id$ */
#include "Encryption.h"

Encryption::Encryption(){
  alphabet = "ABCDEFGHIJKLMNOP";
}

void Encryption::encryptThisString(string st, int shift){
  message = Message(st);
  caesar = Caesar(shift);
  fileHandleChar fh = fileHandleChar();
  int position = 0;
  while(! message.empty() ){
    char next = message.getNextChar();
    string encoded = encode(caesar.encrypt(next));
    fh.passToFile(encoded[0]);
    fh.passToFile(encoded[1]);
    //cout <<encode(next) << ":"
    //     <<decode(encode(next)) << endl;
    if( position++ % 2){
      fh.passToFile(' ');
    }
  }
}

void Encryption::decryptThis(int shift){
  fileHandleString fhs = fileHandleString(); 
  message = Message(fhs.getFromFile());
  decrypted = Message();
  caesar = Caesar(shift);
  while(! message.empty()){
    char next = message.getNextChar();
    if( next != ' '){
      string encoded;
      encoded += next;
      if(! message.empty()){
        encoded += message.getNextChar();
        decrypted.addToContent(caesar.decrypt(decode(encoded)));
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
  //cout << "\n" << s << ":" << original << endl;
  return original;
}

string Encryption::encode(char c){
  int chr = static_cast<int>(c);
  //cout << chr << " " << chr /16 << ":" << chr % 16 << " " << alphabet[chr/16] << alphabet[chr%16];
  string encoded;
  encoded += alphabet[chr/16];
  encoded += alphabet[chr%16];
  return encoded;
}
