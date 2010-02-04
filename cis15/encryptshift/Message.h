/* $Id$ */
#include <stdlib.h>
#include <iostream>
using namespace std;

class Message {
  public:
    Message();
    Message( string new_content);
    void print() const;
    void addToContent(string next);
    void addToContent(char next);
    char getNextChar();
    bool empty();
    void main();
  private:
    string content;
    int location;
};

