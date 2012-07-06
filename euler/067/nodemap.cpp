#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;

struct node{
    node *left;
    int value;
    int level;
    int index;
    node *right;
};
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
    int level = 1;
    int index = 0;
    vector<node*> nodeTree;
    while( ! infile.eof() ){
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
            nodeTree.push_back(n);
            printf("%d:",num);
            pch = strtok(NULL," ");
            index++;
        }
        level++;
        cout << "\n\n";
    }
    vector<node*>::iterator it;

    for ( it=nodeTree.begin() ; it < nodeTree.end(); it++ ){
        node * n;
        n = *it;
        if(n->level < 100){
            n->left = nodeTree[ n->index+n->level ];
            n->right = nodeTree[ n->index+n->level+1 ];
        }
        cout << "v:" <<n->value << " idx:" << n->index << " lvl:" << n->level <<endl;
    }
    cout << nodeTree[0]->left->index << endl;
    cout << nodeTree[0]->left->left->index << endl;
    cout << nodeTree[0]->left->left->left->index << endl;
    cout << nodeTree[0]->left->left->left->left->index << endl;
    return 0;
}
