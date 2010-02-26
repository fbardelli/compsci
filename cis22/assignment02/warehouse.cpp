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
#define ORDER 'o'
#define SHIPMENT 's'
using namespace std;

class warehouse {
  public:
    string cityName;
    int itemQuantity[NUM_ITEMS];
    warehouse * nextWarehouse;
};

void setItemPrices(ifstream& in, float itemPrice[]);

void processOrdersAndShipments(ifstream& inputFile,warehouse warehouses[],float itemPrice[]);
void stringSplit(char * str, const char * delimiters, string parts[], int size);

int main(){
  warehouse warehouses[NUM_WAREHOUSES] = {
    {cityName:"New York", itemQuantity:{0,0,0}},
    {cityName:"Los Angeles", itemQuantity:{0,0,0}},
    {cityName:"Miami", itemQuantity:{0,0,0}},
    {cityName:"Houston", itemQuantity:{0,0,0}},
    {cityName:"Chicago", itemQuantity:{0,0,0}}
  };
  
  float itemPrice[NUM_ITEMS];
  ifstream inputFile;
  inputFile.open("inputFile.dat");
  setItemPrices(inputFile,itemPrice); 
  processOrdersAndShipments(inputFile,warehouses,itemPrice);
  cout << itemPrice[0] << " : " << itemPrice[1] << " : " << itemPrice[2] << endl;
  return 0;
}

void setItemPrices(ifstream& in, float itemPrice[]){
  string line, parts[NUM_ITEMS];
  getline(in,line);
  stringSplit(const_cast<char *>(line.c_str()),"\t",parts,NUM_ITEMS);
  for (int i = 0; i < NUM_ITEMS; i++){
    itemPrice[i] = (float) atof(parts[i].c_str());
  }
}

void processOrdersAndShipments(ifstream& in, warehouse warehouses[],float itemPrice[]){
  string line, parts[5];
  while (getline(in,line) && ! in.eof()){
    //getline(in,line);
    stringSplit(const_cast<char *>(line.c_str()),"\t",parts,5);
    char type = parts[0][0];
    string cityName = parts[1];
    int itemDelta[NUM_ITEMS];
    itemDelta[0] = atoi(parts[2].c_str());
    itemDelta[1] = atoi(parts[3].c_str());
    itemDelta[2] = atoi(parts[4].c_str());
    warehouse * currentWarehouse;
    for(int i = 0; i < NUM_WAREHOUSES; i++){
       if(warehouses[i].cityName == cityName){
         currentWarehouse = &warehouses[i];
       }
    }
    for( int j = 0; j < NUM_ITEMS; j++){
       currentWarehouse->itemQuantity[j] += (type == SHIPMENT ? itemDelta[j] : -itemDelta[j]);
    }
    cout << type << " : " << currentWarehouse->cityName << " : " 
         << currentWarehouse->itemQuantity[0] << " : " 
         << currentWarehouse->itemQuantity[1] << " : " 
         << currentWarehouse->itemQuantity[2] << endl;
  }
}

void stringSplit(char * str, const char * delimiters, string parts[], int size){
  char * pch = strtok(str,delimiters);
  int i = 0;
  while (pch != NULL && i < size){
    parts[i++] = string(pch);
    pch = strtok (NULL, delimiters);
  }
}

