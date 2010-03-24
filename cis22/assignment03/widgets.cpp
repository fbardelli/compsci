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
using namespace std;

struct receipt {
  int quantity;
  double cost;
};

class promotion {
  int percentage;
  int usesRemaining;
  bool isActive;
  public:
    promotion(){
          
    }
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
      usesRemaining--;
      if(usesRemaining < 1){
        deactivate();
      }
    }
    float getPromo() {
      if(isActive){
        usePromo();
      }
      return 1.0f + (percentage * 0.01f);
    }
};

class inventory {
  list<receipt> rList;
  public:
    inventory(){}
    void add(receipt r){
      //cout << "pushing: q" << r.quantity << "c" << r.cost << endl;
      rList.push_back(r);
      //cout << "size after push "<< rList.size() <<endl;
    }
    void processOrder(int desiredQuantity, promotion p){
      //while we have wigets in stock and the customer needs widgets
      float total_cost = 0.0f;
      float currentPromoModifier = p.getPromo();
      //cout << "size: "<<rList.size()<<endl;
      while ( ! rList.empty() && desiredQuantity > 0){
        //receipt r = rList.front();
        int sold = 0;
        float cost = rList.front().cost;
        if (rList.front().quantity > desiredQuantity){
          rList.front().quantity -= desiredQuantity;
          sold = desiredQuantity;
          desiredQuantity = 0;
        }else{
          desiredQuantity -= rList.front().quantity;
          sold = rList.front().quantity;
          //cout <<"REMOVING";
          //cout << "size was: " << rList.size();
          rList.pop_front();
          //cout << " size is: " << rList.size() <<"\n";
        }
        float current_sale = sold * cost;
        cout << sold << " at " << cost << " each  Sales:\t $" << current_sale << endl; 
        total_cost += current_sale; 
      }
      if (desiredQuantity>0){
      cout << "Remainder of "<< desiredQuantity<<" widgets not availible\n";
      }
      cout << "\tTotal Sale:\t $" <<  total_cost << endl;
    }
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
        //cout << "promo ";
        pch = strtok (NULL, delimiter);
        percent = atoi(pch);
        promo.activate(percent);
        //cout << "pct :" << percent << "%\n";
        break;
      case 'S':
        //cout << "sales ";
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        stock.processOrder(quantity,promo);
        //cout << "SALES QTY :" << quantity << "\n";
        break;
      case 'R':
        //cout << "receipt ";
        pch = strtok (NULL, delimiter);
        quantity = atoi(pch);
        pch = strtok (NULL, delimiter);
        cost = atof(pch);
        receipt r = {quantity,cost};
        stock.add(r);
        //cout << "qty :" << quantity << " cost :" << cost << "\n";
        break;
    }
  }
}


//  while (pch != NULL && i < size){
//    parts[i++] = string(pch);
//    pch = strtok (NULL, delimiters);

