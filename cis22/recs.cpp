#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
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
    transaction(int cId, int tId, float pay):transactionId(tId),customerId(cId),type(PAYMENT){
      data.payment = pay;
    }
    transaction(int cId, int tId, char n[],int qty, float pr):transactionId(tId),customerId(cId),type(ORDER){
      data.order.quantity = qty; 
      data.order.price = pr;
      /*copy up to 1st 20 characters*/
      int last =0;
      for(int i = 0;i < strlen(n) && i < 20;i++){
        data.order.name[i] = n[i];
        last = i;
      }
      data.order.name[++last] = '\0';
    }
};

struct customer {
    int id;
    string name;
    float balance;
    list<transaction> transactions;
    customer(){};
    customer(int i,string n,float b):id(i),name(n),balance(b){}
};

customer * parseCustomerRecord(string record);
transaction parseTransactionRecord(string record);
void getCustomerTransactions(customer c, list<transaction> t);
void stringSplit(string str, char delimiter, list<string>& parts);

int main(){
  list<customer *> customers;
  ifstream masterFile,transactionFile;
  string customerLine,transactionLine;
  masterFile.open("master.dat");
  transactionFile.open("transactions.dat");
  int currentCustomerId = -1;
  customer * cust;
  if(transactionFile.is_open()){
    while(! transactionFile.eof() ){
       getline(transactionFile,transactionLine);
       if (transactionLine.length() > 0){
         transaction trans = parseTransactionRecord(transactionLine);
         /* grab next customer record when the transaction switches to new user
            keep going until we get the right customer.  This will only work if
            both files are sorted by customer id.
         */
         while(trans.customerId != currentCustomerId){
           if(masterFile.is_open()){
             if(! masterFile.eof() ){
               getline(masterFile,customerLine);
               if (customerLine.length() > 0){
                 cust = parseCustomerRecord(customerLine);
                 customers.push_back(cust);
                 currentCustomerId = cust->id;
               }
             }else{
                cout << "ERROR: reached end of master file";
                exit(1);
             }
           }
         }
         cust->transactions.push_back(trans);
       }
    }
  }
  

  

  for(list<customer *>::iterator current = customers.begin();current != customers.end(); ++current){
     cout << (*current)->name << endl;
     float balance = (*current)->balance;
     for(list<transaction>::iterator txn = (*current)->transactions.begin();txn != (*current)->transactions.end(); ++txn){
       if (txn->type == ORDER){
         int quantity = txn->data.order.quantity;
         float price = txn->data.order.price;
         float subtotal = (price*quantity);
         balance += subtotal;
         cout << "\t * "<< txn->data.order.name << "\t" << price << "\t" <<quantity << "\t" << subtotal << endl;
       } else {
         float payment = txn->data.payment;
         cout << "\t * "<< "PAYMENT\t\t\t\t" << payment <<  endl;
         balance -= payment;
       }
     }
     cout << "\t\t\t\t\tTOTAL\t" << balance <<  endl;
     delete *current;
  }

  return 0;
}


transaction parseTransactionRecord(string record){
  list <string> parts;
  stringSplit(record,'\t', parts);
  char type = parts.front().at(0);
  parts.pop_front();
  int custId = atoi( parts.front().c_str() );
  parts.pop_front();
  int transId = atoi( parts.front().c_str() );
  parts.pop_front();
  if (type == PAYMENT) {
    float amount = (float)atof(parts.front().c_str());
    transaction t(custId,transId,amount);
    return t;
  } else if (type == ORDER){
    string item_name = parts.front();
    parts.pop_front();
    int item_qty = atoi(parts.front().c_str());
    parts.pop_front();
    float item_price = (float)atof(parts.front().c_str());
    transaction t(custId,transId,const_cast<char *>(item_name.c_str()),item_qty,item_price);
    return t;
  } else {
    cout << "type unknown";
    exit(1);
  }
}

customer * parseCustomerRecord(string record){
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
  customer * c = new customer(id,name,balance);
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
