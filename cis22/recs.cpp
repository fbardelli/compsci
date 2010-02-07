#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<list>
#include<cstdio>
using namespace std;
#define ORDER 'O'
#define PAYMENT 'P'

struct transaction {
    char type;
    int transactionId;
    int customerId;
    union {
      struct {
        char name[21];
        int quantity;
        float price;
      } order;
      float payment;
    } data;
    transaction(int tId, int cId, float pay):type(PAYMENT){
      data.payment = pay;
    }
    transaction(char n[],int qty, float pr):type(ORDER){
      data.order.quantity = qty; 
      data.order.price = pr;
    }
};

struct customer {
    int id;
    string name;
    float balance;
    list<transaction> transactions;
    customer(int i,string n,float b):id(i),name(n),balance(b){}
};

customer parseCustomerRecord(string record);
transaction parseTransactionRecord(string record);
void getCustomerTransactions(customer c, list<transaction> t);
void stringSplit(string str, char delimiter, list<string>& parts);

int main(){
  list<customer> customers;
  list<transaction> allTransactions;
  ifstream masterFile,transactionFile;
  string customerLine,transactionLine;
  masterFile.open("master.dat");
  transactionFile.open("transaction.dat");
  if(transactionFile.is_open()){
    while(! transactionFile.eof() ){
       getline(transactionFile,transactionLine);
       if (transactionLine.length() > 0){
         allTransactions.push_back(parseTransactionRecord(transactionLine));
       }
    }
  }
  if(masterFile.is_open()){
    while(! masterFile.eof() ){
       getline(masterFile,customerLine);
       if (customerLine.length() > 0){
         customer c = parseCustomerRecord(customerLine);
         cout <<  "r: " << c.id << " name: " << c.name
              << " bal: " << c.balance <<endl;
         //getCustomerTransactions(c,allTransactions);
       }
    }
  }
}

void getCustomerTransactions(customer c, list<transaction> t){
}

transaction parseTransactionRecord(string record){

}

customer parseCustomerRecord(string record){
  int id;
  string name;
  float balance;
  list<string> parts;
  stringSplit(record,'\t',parts);
  id = atoi( parts.front().c_str() );
  parts.pop_front();
  name = parts.front();
  parts.pop_front();
  if(name.length() > 20){
    cout << "invalid record, name is too long";
    exit(1);
  }
  balance = (float) atof( parts.front().c_str() );
  parts.pop_front();
  customer c(id,name,balance);
  return c;
}


void stringSplit(string str, char delimiter, list<string>& parts){
  int delimiterPos;
  while( (delimiterPos = str.find_first_of(delimiter)) != str.npos ) {
    if(delimiterPos > 0) {
      parts.push_back(str.substr(0,delimiterPos));
    }
    str = str.substr(delimiterPos+1);
  }
  if(str.length() > 0){
     parts.push_back(str);
  }
}
