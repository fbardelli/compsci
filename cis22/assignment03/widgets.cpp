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
#define NUM_WAREHOUSES 5
#define NUM_ITEMS 3
#define ORDER 'o'
#define SHIPMENT 's'
using namespace std;


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
  while (getline(in,line) && ! in.eof()){
    /* File contains: type cityName amount1 amount2 amount3 */
    const char * delimiter = "\t";
    char * pch = strtok((char *)line.c_str(),delimiter);
    string type = string(pch);
    int percent, quantity;
    double cost;
    switch(type.at(0)){
      case 'P':
        cout << "promo ";
        pch = strtok (NULL, delimiter);
        percent = atoi(pch);
        cout << "pct :" << percent << "%\n";
        break;
      case 'S':
        cout << "sales ";
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        cout << "qty :" << quantity << "\n";
        break;
      case 'R':
        cout << "receipt ";
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        pch = strtok (NULL, delimiter);
        cost = atof(pch);
        cout << "qty :" << quantity << " cost :" << cost << "\n";
        break;
    }
  }
}


//  while (pch != NULL && i < size){
//    parts[i++] = string(pch);
//    pch = strtok (NULL, delimiters);

