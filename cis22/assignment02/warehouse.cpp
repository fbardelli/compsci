/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #2
 *  February 22, 2009
 */
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<list>
#define NUM_WAREHOUSES 5
#define NUM_ITEMS 3
using namespace std;

struct warehouse {
  string cityName;
  int itemQuantity[NUM_ITEMS];
};

void setItemPrices(ifstream *in, float itemPrice[], int size);
void stringSplit(char * str, const char * delimiters, string parts[]);

int main(){
  warehouse warehouses[NUM_WAREHOUSES] = {
    {cityName:"New York", itemQuantity:{0,0,0}},
    {cityName:"Los Angeles", itemQuantity:{0,0,0}},
    {cityName:"Miami", itemQuantity:{0,0,0}},
    {cityName:"Houston", itemQuantity:{0,0,0}},
    {cityName:"Chicago", itemQuantity:{0,0,0}}
  };
  
  float itemPrice[NUM_ITEMS];
  ifstream * inputFile;
  inputFile->open("inputFile.dat");
  setItemPrices(inputFile,itemPrice,NUM_ITEMS); 
  return 0;
}

void setItemPrices(ifstream * in, float itemPrice[], int size){
  string line;
  getline(in,line);
  cout << line;
}

void stringSplit(char * str, const char * delimiters, string parts[]){
  char * pch = strtok(str,delimiters);
  int i = 0;
  while (pch != NULL){
    parts[i++] = string(pch);
    pch = strtok (NULL, delimiters);
  }
}

