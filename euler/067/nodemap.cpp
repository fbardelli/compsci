#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
using namespace std;

struct node{
    node *left;
    int value;
    int level;
    int index;
    int sum;
    node *right;
};

void bestPath(node * node);
void processTree(vector<vector<node*> > rows);
/**
     0
    1 2
   3 4 5
  6 7 8 9
10 11 12 13
**/
int main(){
    ifstream infile;
    infile.open("triangle.txt", ifstream::in);
    if(! infile.is_open()){
        cerr << "Failed to open triangle file\n";
        exit(1);
    }
    int level = 1;
    int index = 0;
    vector<node*> nodeTree;
    vector<vector<node*> > rows;
    int sum = 0;
    int average = 0;
    while( ! infile.eof() ){
        vector<node*> row;
        char buffer[512];
        infile.getline(buffer,512);
        char * pch;
        pch = strtok(buffer," ");
        while( pch != NULL){
            node *n;
            n = new node;
            int num = atoi(pch);
            n->left = 0;
            n->right = 0;
            n->level = level;
            n->index = index;
            n->value = num;
            n->sum = num;
            sum += num;
            row.push_back(n);
            nodeTree.push_back(n);
            //printf("%d:",num);
            pch = strtok(NULL," ");
            index++;
        }
        if(row.size()>0){
            rows.push_back(row);
        }
        level++;
    }
    average = sum / index;
    cout << average << " = " << sum << " / " << index << endl;
    vector<node*>::iterator it;

    for ( it=nodeTree.begin() ; it < nodeTree.end(); it++ ){
        node * n;
        n = *it;
        if(n->level < 100){
            n->left = nodeTree[ n->index+n->level ];
            n->right = nodeTree[ n->index+n->level+1 ];
        }
    }
    processTree(rows);
    return 0;
}

void processTree(vector<vector<node*> > rows) {
    int startRow = rows.size() - 2;
    for( int i = startRow; i >= 0; i-- ){
        vector<node*> row;
        row = rows[i];
        vector<node*>::iterator it;

        for ( it=row.begin() ; it < row.end(); it++ ){
            node * n;
            n = *it;
            if(n->left->sum > n->right->sum){
                n->sum = n->left->sum + n->value;
            }else{
                n->sum = n->right->sum + n->value;
            }
        }
    }
    cout << "highest sum " << rows[0][0]->sum << endl;
    bestPath(rows[0][0]);
}


void bestPath(node * node){
    while(node->level < 100 ){
        cout << node->value << "(" << node->level << ") =>"; 
        if(node->left->sum > node->right->sum)
            node = node->left;
        else
            node = node->right;
    }
    cout << node->value << "(" << node->level << ")\n"; 
}
