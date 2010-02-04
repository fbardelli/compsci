/* $Id$ */
#include "Message.h"

Message::Message(){
  content = "";
  location = 0;
}

Message::Message(string new_content){
  content = new_content;
  location = 0;
}

void Message::print() const{
  cout << content;
}

void Message::addToContent(string next){
  content.append(next);
}

void Message::addToContent(char next){
  content.append(1,next);
}

char Message::getNextChar(){
  return content[location++];
}

bool Message::empty(){
  return(content[location] == '\0');
}

void Message::main(){
  Message n = Message("sewage");
  n.addToContent(" smells bad");
  n.addToContent("\n");
  n.addToContent('a');
  char b = 'b';
  n.addToContent(b);
  n.print();
  while(! n.empty() ){
    cout << n.getNextChar() << ".";
  }
}

