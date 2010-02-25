/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #2
 *  February 22, 2009
 */
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<list>
#define NUM_WAREHOUSES 5
#define NUM_ITEMS 3
using namespace std;

struct warehouse {
  string cityName;
  int itemAmount[3];
};

setItemPrices(ifstream * in, int itemPrice[]);

int main(){
  warehouse warehouses[NUM_WAREHOUSES];
  float itemPrice[NUM_ITEMS];
  ifstream * inputFile;
  inputFile->open("inputFile.dat");
  setItemPrices(inputFile,itemPrice,NUM_ITEMS); 
  return 0;
}

setItemPrices(ifstream * in, int itemPrice[], int size){

}

void stringSplit(char * str, const char * delimiters, string parts[]){
  char * pch = strtok(str,delimiters);
  int i = 0;
  while (pch != NULL){
    parts[i++] = string(pch);
    pch = strtok (NULL, delimiters);
  }
}

