#include<iostream>
#include<iomanip>
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
    list<transaction *> transactions;
    customer(){};
    customer(int i,string n,float b):id(i),name(n),balance(b){}
};

customer * parseCustomerRecord(string record);
transaction * parseTransactionRecord(string record);
void getCustomerTransactions(customer c, list<transaction> t);
void stringSplit(char * string1, const char * delimiters, string parts[]);
void writeReport(list<customer *> customers);
void updateMasterFile(list<customer *> customers);

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
         transaction * trans = parseTransactionRecord(transactionLine);
         /* grab next customer record when the transaction switches to new user
            keep going until we get the right customer.  This will only work if
            both files are sorted by customer id.
         */
         while(trans->customerId != currentCustomerId){
           if(masterFile.is_open()){
             if(! masterFile.eof() ){
               getline(masterFile,customerLine);
               if (customerLine.length() > 0){
                 cust = parseCustomerRecord(customerLine);
                 customers.push_back(cust);
                 currentCustomerId = cust->id;
               }
             }else{
                cout << "ERROR: reached end of master file before end of transactions";
                exit(1);
             }
           }
         }
         cust->transactions.push_back(trans);
       }
    }
  }
  masterFile.close();
  transactionFile.close();
  
  writeReport(customers);
  updateMasterFile(customers);
  return 0;
}

void updateMasterFile(list<customer *> customers){
  /* iterate through list of customers */
  ofstream master;
  master.open("master.dat",ios::out);
  for(list<customer *>::iterator current = customers.begin();current != customers.end(); ++current){
    master << (*current)->id << "\t" << (*current)->name << "\t" <<(*current)->balance << endl;
    delete * current;
  }
}

void writeReport(list<customer *> customers){
  /* iterate through list of customers */
  for(list<customer *>::iterator current = customers.begin();current != customers.end(); ++current){
    float balance = (*current)->balance;
    cout << setw(20) << left << (*current)->name << "\t" << (*current)->id <<  endl;
    cout << setw(45) << right << "Previous Balance:\t$" << balance <<  endl;
    /* For each customer iterate through transactions writing lines for orders and payments*/
    for(list<transaction *>::iterator txnp = (*current)->transactions.begin();txnp != (*current)->transactions.end(); ++txnp){
      transaction * txn = *txnp;
      if (txn->type == ORDER){
        int quantity = txn->data.order.quantity;
        float price = txn->data.order.price;
        float subtotal = (price*quantity);
        balance += subtotal;
        cout << txn->transactionId << "\t"<< setw(20) << left <<txn->data.order.name << "\t" << price << "\t" <<quantity << "\t$" << subtotal << endl;
      } else {
        float payment = txn->data.payment;
        cout << txn->transactionId << "\t"<< "**PAYMENT\t\t\t\t-$" << payment <<  endl;
        balance -= payment;
      }
      (*current)->balance = balance;
      delete txn;
    }
    cout << setw(45) << right << "Balance Due:\t$" << balance << "\n\n";
    //cout << "\t\t\t\t\tTOTAL\t" << balance <<  endl;
  }
}

transaction * parseTransactionRecord(string record){
  string parts[6];
  /* split line into type, customerId, transactionId... */
  stringSplit(const_cast<char *>(record.c_str()),"\t", parts);
  char type = parts[0].at(0);
  int custId = atoi( parts[1].c_str() );
  int transId = atoi( parts[2].c_str() );
  /* depending on transaction type different fields will be in the file 
     payment has paymentAmount
     order has itemName, itemQuantity, itemPrice
  */
  if (type == PAYMENT) {
    float amount = (float)atof(parts[3].c_str());
    transaction * t = new transaction(custId,transId,amount);
    return t;
  } else if (type == ORDER){
    string itemName = parts[3];
    int itemQuantity = atoi(parts[4].c_str());
    float itemPrice = (float)atof(parts[5].c_str());
    transaction * t = new transaction(custId,transId,const_cast<char *>(itemName.c_str()),itemQuantity,itemPrice);
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
  string parts[3];
  /* split line into id, name, balance */
  stringSplit(const_cast<char *>(record.c_str()),"\t", parts);
  id = atoi( parts[0].c_str() );
  name = parts[1];
  if(name.length() > 20){
    cout << "invalid record, name is too long";
    exit(1);
  }
  balance = (float) atof( parts[2].c_str() );
  customer * c = new customer(id,name,balance);
  return c;
}

/* split large string into smaller strings breaking on delimiter */
void stringSplit(char * str, const char * delimiters, string parts[]){
  char * pch = strtok(str,delimiters);
  int i = 0;
  while (pch != NULL){
    parts[i++] = string(pch);
    pch = strtok (NULL, delimiters);
  }
}

