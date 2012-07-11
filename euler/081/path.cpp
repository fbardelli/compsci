#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;

struct node{
    node *down, *right;
    int value, sum;
};

int main(){
    ifstream infile;
    infile.open("matrix.txt", ifstream::in);
    if(! infile.is_open()){
        cerr << "Failed to open matrix file\n";
        exit(1);
    }
    vector<vector<node*> > matrix;
    while( ! infile.eof() ){
        vector<node*> row;
        char buffer[512];
        infile.getline(buffer,512);
        char * pch;
        pch = strtok(buffer,",");
        while( pch != NULL){
            node *n;
            n = new node;
            int num = atoi(pch);
            n->down = n->right = 0;
            n->sum = 0;
            n->value = num;
            row.push_back(n);
            pch = strtok(NULL,",");
        }
        if(row.size()>0){
            matrix.push_back(row);
        }
    }
    for ( int x = 79; x >= 0; x--){ 
        for ( int y = 79; y >= 0; y--){ 
            node * me;
            me = matrix[y][x];
            if(y > 0){
                matrix[y-1][x]->down = me;
            }
            if(x > 0){
                matrix[y][x-1]->right = me;
            }
            int minimal = 0;
            if(me->right !=0){
                minimal = me->right->sum;
                if(me->down !=0){
                    if(me->down->sum < minimal){
                        minimal = me->down->sum;
                    }
                }
            }else if(me->down !=0){
                minimal = me->down->sum;
            }             
            me->sum = me->value + minimal;
        }
    }
    cout << "minimal sum:" << matrix[0][0]->sum << endl;
    return 0;
}
