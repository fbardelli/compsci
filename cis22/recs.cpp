#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<list>
using namespace std;

class customer {
  public:
    int id;
    string name;
    float balance;
    customer(int i,string n,float b){
      id = i;
      name = n;
      balance = b;
    }
};


customer parseRecord(string rec);
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
         customer c = parseRecord(customerLine);
       }
    }
  }
}

customer parseRecord(string record){
  int startpos = 0, pos =0;
  pos = record.find(':',startpos);
  int id =  atoi(record.substr(startpos,pos).c_str());
  startpos = pos + 1;
  pos = record.find(':',startpos);
  string name = record.substr(startpos,pos-startpos);
  startpos = pos + 1;
  float balance = (float) atof(record.substr(startpos).c_str());
  //cout <<  "s:" << startpos << " e:" << pos <<endl;
  cout <<  "r: " << id << " name: " << name
       <<  " b: " << id << " bal: " << balance <<endl;
  customer c(id,name,balance);
  return c;
}
