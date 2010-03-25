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
#define MARKUP 1.3f
using namespace std;
#include <sstream> // header file for string stream processing
using std::ostringstream; // stream insertion operators

void processRecords( ifstream& in );

struct receipt {
  int quantity;
  double cost;
};

class promotion {
  int percentage;
  int usesRemaining;
  bool isActive;
  public:
    promotion(){}
    void activate(int p){
      isActive = true;
      usesRemaining = 2;
      percentage =  p;
    }
    void deactivate(){
      isActive = false;
      usesRemaining = 0;
      percentage = 0;
    }
    void usePromo(){
      if(usesRemaining-- < 1){
        deactivate();
      }
    }
    int getDiscount(){
      return percentage;
    }
    float getPromo() {
      if(isActive){
        usePromo();
      }
      return 1.0f - (percentage * 0.01f);
    }
};

class inventory {
  list<receipt> rList;
  public:
    inventory(){}
    void add(receipt r){
      rList.push_back(r);
    }
    void processOrder(int requestedQuantity, promotion * p){
      float totalCost = 0.0f;
      float currentPromoModifier = p->getPromo();
      int neededQuantity = requestedQuantity;
      ostringstream outputString;
      outputString << fixed << setprecision(2);
      
      //while we have widgets in stock and the customer needs widgets
      while ( ! rList.empty() && neededQuantity > 0){
        //receipt r = rList.front();
        int sold = 0;
        float cost = rList.front().cost;
        if (rList.front().quantity > neededQuantity){
          rList.front().quantity -= neededQuantity;
          sold = neededQuantity;
          neededQuantity = 0;
        }else{
          neededQuantity -= rList.front().quantity;
          sold = rList.front().quantity;
          //no more items left at this price
          rList.pop_front();
        }
        float current_sale = sold * cost * MARKUP;
        outputString << sold << " @ " << ( cost * MARKUP ) << " each Sales:\t$" << current_sale << endl; 
        totalCost += current_sale; 
      }

      //If the customer still needs widgets and we dont have any
      if (neededQuantity>0){
         outputString << "Remainder of "<< neededQuantity<<" widgets not availible\n";
      }
      
      //process discount if there's one active
      int discount = p->getDiscount();
      float discountedCost = totalCost * currentPromoModifier;
      if(totalCost != discountedCost){
         outputString << "\tOriginal Sale:\t$" <<  totalCost << endl;
         outputString << "\tDiscount " << discount <<"%\t-$" << totalCost-discountedCost << endl;
         totalCost = discountedCost;
      }
      outputString << "\tTotal Sale:\t$" << totalCost << "\n\n";
      cout << "Sold " << requestedQuantity-neededQuantity 
           << " of " << requestedQuantity << " widgets\n";
      cout << outputString.str();
    }
};




int main(){
  ifstream inputFile;
  inputFile.open("records.dat");
  processRecords(inputFile);
  return 0;
}

void processRecords( ifstream& in ){
  string line, parts[3];
  /* Read in file */
  inventory stock;
  promotion promo;
  while (getline(in,line) && ! in.eof()){
    //split on tab and get record type
    const char * delimiter = "\t";
    char * pch = strtok((char *)line.c_str(),delimiter);
    string type = string(pch);

    //parse record differently based on record type.
    int percent, quantity;
    double cost;
    switch(type.at(0)){
      case 'P':
        pch = strtok (NULL, delimiter);
        percent = atoi(pch);
        cout << "Read in a " << percent << "\% promotion\n\n";
        promo.activate(percent);
        break;
      case 'S':
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        cout << "Processing sale of " << quantity << " widgets\n";
        stock.processOrder(quantity,&promo);
        break;
      case 'R':
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        pch = strtok (NULL, delimiter);
        cost = atof(pch);
        cout << "Received " << quantity << " widgets at $" 
             << setprecision(2) << fixed << cost <<" each"
             <<"($" << cost * MARKUP <<" after 30% markup)\n\n";
        receipt r = {quantity,cost};
        stock.add(r);
        break;
    }
  }
}


