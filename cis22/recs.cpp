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
    customer(string record){
      int startpos = 0, pos =0;
      pos = record.find(':',startpos);
      id =  atoi(record.substr(startpos,pos).c_str());
      startpos = pos + 1;
      pos = record.find(':',startpos);
      name = record.substr(startpos,pos-startpos);
      cout <<  "s:" << startpos << " e:" << pos <<endl;
      cout <<  "r: " << id << " name: " << name <<endl;
    }
};

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
         customer c(customerLine);
       }
    }
  }
}
