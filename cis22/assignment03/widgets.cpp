/*  Frank Bardelli
 *  CIS 22 Data Structures
 *  Assignment #2
 *  February 22, 2009
 */
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<list>
#define PROMO   'P'
#define SALE    'S'
#define RECEIPT 'R'
using namespace std;

struct stock {
  int quantity;
  double cost;
};

struct promo {
  int discountPercent;
  int usesRemaining;
  bool active;
};

//void stringSplit( char * str, const char * delimiters, string parts[], int size );
void processRecords( ifstream& in );

int main(){
  ifstream inputFile;
  inputFile.open("records.dat");
  processRecords(inputFile);
  return 0;
}

void processRecords( ifstream& in ){
  string line, parts[3];
  /* Read in file */
  list<stock> itemStock;
  while (getline(in,line) && ! in.eof()){
    /* File contains: type cityName amount1 amount2 amount3 */
    const char * delimiter = "\t";
    char * pch = strtok((char *)line.c_str(),delimiter);
    string type = string(pch);
    int percent, quantity;
    double cost;
    //stock st;
    switch(type.at(0)){
      case PROMO:
        cout << "promo ";
        pch = strtok (NULL, delimiter);
        percent = atoi(pch);
        cout << "pct :" << percent << "%\n";
        break;
      case SALE:
        cout << "sales ";
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        cout << "qty :" << quantity << "\n";
        break;
      case RECEIPT:
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        pch = strtok (NULL, delimiter);
        cost = atof(pch);
        stock st = {quantity,cost};
        itemStock.push_back(st);
        cout << quantity << " widgets received at cost:$" << cost << "\n";
        break;
    }
  }
  for(list<stock>::iterator current = itemStock.begin();current != itemStock.end(); ++current){
    cout << current->quantity << "::" << current->cost << endl;
  }
}


//  while (pch != NULL && i < size){
//    parts[i++] = string(pch);
//    pch = strtok (NULL, delimiters);

