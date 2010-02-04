/* $Id$ */
#include <stdlib.h>
#include <iostream>
#include "Message.h"
#include "Caesar.h"
#include "fileHandleChar.h"
#include "fileHandleString.h"

using namespace std;

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

