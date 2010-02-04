/* $Id$ */
#include "Caesar.h"

Caesar::Caesar(){

}

Caesar::Caesar(int s){
  shift = s;
}

void Caesar::setShift(int s){
  shift = s;
}

char Caesar::encrypt(char c){
  int chr = static_cast<int>(c);
  int alpha_offset;
  //need an offset so the modulus operation will work
  if (c >= 'a' && c <= 'z'){
    alpha_offset = static_cast<int>('a');
  }else if (c >= 'A' && c <= 'Z'){
    alpha_offset = static_cast<int>('A');
  } else {
    //return non-alpha characters
    return c;  
  }
  //Add the shift to the character, remove the offset to bring chr into the 0-25 range 
  char new_letter = static_cast<char>( ( ( (chr + shift) - alpha_offset) % 26) + alpha_offset  );
  return new_letter;
}

char Caesar::decrypt(char c){
  int chr = static_cast<int>(c);
  int alpha_offset;
  //need an offset so the modulus operation will work
  if (c >= 'a' && c <= 'z'){
    alpha_offset = static_cast<int>('a');
  }else if (c >= 'A' && c <= 'Z'){
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


