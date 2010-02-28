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

class warehouse {
  public:
    string cityName;
    int itemQuantity[NUM_ITEMS];
    warehouse * nextWarehouse;
};

void setItemPrices(ifstream& in, float itemPrice[]);
void processOrdersAndShipments(ifstream& inputFile,warehouse warehouses[],float itemPrice[]);
float processOrder( warehouse * currentWarehouse,int itemNumber,float itemPrice,int itemDelta);
void stringSplit(char * str, const char * delimiters, string parts[], int size);
void printSummary(warehouse * currentWarehouse, char type, float totalPrice);

int main(){
  /* initialize warehouses with 0 items */
  warehouse warehouses[NUM_WAREHOUSES] = {
    {cityName:"New York", itemQuantity:{0,0,0}},
    {cityName:"Los Angeles", itemQuantity:{0,0,0}},
    {cityName:"Miami", itemQuantity:{0,0,0}},
    {cityName:"Houston", itemQuantity:{0,0,0}},
    {cityName:"Chicago", itemQuantity:{0,0,0}}
  };
  /* setup pointers to next warehouse*/
  for(int i = 0; i <= NUM_WAREHOUSES; i++){
    warehouses[i].nextWarehouse = &warehouses[ (i+1)%NUM_WAREHOUSES ];
  }
  
  float itemPrice[NUM_ITEMS];
  ifstream inputFile;
  inputFile.open("inputFile.dat");
  setItemPrices(inputFile,itemPrice); 
  processOrdersAndShipments(inputFile,warehouses,itemPrice);
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
  /* Read in file */
  while (getline(in,line) && ! in.eof()){
    cout << line << endl;
    stringSplit(const_cast<char *>(line.c_str()),"\t",parts,5);
    char type = parts[0].at(0);
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
    float totalPrice = 0.0f;
    float costModifier[NUM_ITEMS] = { 1.0f, 1.0f, 1.0f};
    for( int j = 0; j < NUM_ITEMS; j++){
       if(type == SHIPMENT){
         currentWarehouse->itemQuantity[j] += itemDelta[j]; 
       }else if(type == ORDER){
         totalPrice += processOrder(currentWarehouse,j,itemPrice[j],itemDelta[j]);

//         int neededItems = currentWarehouse->itemQuantity[j] - itemDelta[j];
//         if(neededItems >=0){ 
//            currentWarehouse->itemQuantity[j] -= itemDelta[j];
//         }else{
//            /* If current warehouse does not have enough items check other warehouses */
//            warehouse * pWarehouse = currentWarehouse;
//            for(int i = 0; i<= NUM_WAREHOUSES; i++){
//               if( pWarehouse->nextWarehouse->itemQuantity[j] + neededItems > 0){
//                 /* Item found, move items from warehouse with surplus to current warehouse */
//                 cout <<  -neededItems << " of item #" << j+1 <<" shipped from " << pWarehouse->nextWarehouse->cityName <<
//                      " to " << currentWarehouse->cityName << endl;
//                 pWarehouse->nextWarehouse->itemQuantity[j] += neededItems;
//                 currentWarehouse->itemQuantity[j] -= neededItems;
//                 /* Add a 10% charge for shipping from another warehouse */
//                 costModifier[j] = 1.1f;
//                 break;
//               }else{
//                 if( pWarehouse->nextWarehouse->cityName == currentWarehouse->cityName){
//                   cout << "Order for item #"<< j+1 << " unfilled" << endl;
//                   /*ship none of the item if order can't be filled */
//                   itemDelta[j] = 0;
//                   break;
//                 }
//                 pWarehouse = pWarehouse->nextWarehouse;
//               }
//            }
//         }
//         totalPrice += (itemDelta[j] * ( itemPrice[j] * costModifier[j] ));

       }else{
         cout <<"invalid record type '"<<type <<", skipping";
       }
    }
    printSummary(currentWarehouse,type,totalPrice);
  }
}

float processOrder( warehouse * currentWarehouse,int itemNumber,float itemPrice,int itemDelta){
  int neededItems = currentWarehouse->itemQuantity[itemNumber] - itemDelta;
  float costModifier = 1.0f;
  if(neededItems >=0){ 
     currentWarehouse->itemQuantity[itemNumber] -= itemDelta;
  }else{
     /* If current warehouse does not have enough items check other warehouses */
     warehouse * pWarehouse = currentWarehouse;
     for(int i = 0; i<= NUM_WAREHOUSES; i++){
        if( pWarehouse->nextWarehouse->itemQuantity[itemNumber] + neededItems > 0){
          /* Item found, move items from warehouse with surplus to current warehouse */
          cout <<  -neededItems << " of item #" << itemNumber+1 <<" shipped from " << pWarehouse->nextWarehouse->cityName <<
               " to " << currentWarehouse->cityName << endl;
          pWarehouse->nextWarehouse->itemQuantity[itemNumber] += neededItems;
          currentWarehouse->itemQuantity[itemNumber] -= neededItems;
          /* Add a 10% charge for shipping from another warehouse */
          costModifier = 1.1f;
          break;
        }else{
          if( pWarehouse->nextWarehouse->cityName == currentWarehouse->cityName){
            cout << "Order for item #"<< itemNumber+1 << " unfilled" << endl;
            /*ship none of the item if order can't be filled */
            itemDelta = 0;
            break;
          }
          pWarehouse = pWarehouse->nextWarehouse;
        }
     }
  }
  return (float) (itemDelta * ( itemPrice * costModifier ));
}

void printSummary(warehouse * currentWarehouse, char type, float totalPrice){
  cout << setw(10) << left << currentWarehouse->cityName << "\t" 
       << currentWarehouse->itemQuantity[0] << "\t" 
       << currentWarehouse->itemQuantity[1] << "\t" 
       << currentWarehouse->itemQuantity[2] << endl;
  if(type == ORDER){  
    cout << "Price of Order:\t$" << totalPrice <<endl;
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

