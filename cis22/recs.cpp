#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<list>
#include<cstdio>
using namespace std;

class transaction {
  public:
    char type;
    union {
      struct {
        char name[20];
        int quantity;
        float price;
      } order;
      float payment;
    } data;
    transaction(float p){
      type = 'P';
      data.payment = p;
    }
};

class customer {
  public:
    int id;
    string name;
    float balance;
    list<transaction> transactions;
    customer(int i,string n,float b):id(i),name(n),balance(b){}
};

customer parseCustomerRecord(string rec);

int main(){
  list<customer> customers;
  ifstream masterFile,transactionFile;
  string customerLine;
  masterFile.open("master.dat");
  //transactionFile.open("transaction.dat");
  if(masterFile.is_open()){
    while(! masterFile.eof() ){
       getline(masterFile,customerLine);
       if (customerLine.length() > 0){
         customer c = parseCustomerRecord(customerLine);
         cout <<  "r: " << c.id << " name: " << c.name
              << " bal: " << c.balance <<endl;
       }
    }
  }
}

customer parseCustomerRecord(string record){
  int id;
  char name[20];
  float balance;
  sscanf(record.c_str(),"%i\t%s\t%f",&id,name,&balance);
  customer c(id,string(name),balance);
  return c;
}
