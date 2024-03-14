#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


bool currPaths(Node* curr, int currTotal, int& total){
    Node* currL = curr->left;
    Node* currR = curr->right;
    if ((currL != nullptr) || (currR != nullptr)){
        currTotal++;
        bool L, R;
        if (currL != nullptr){
            L = currPaths(curr->left, currTotal, total);
            if (L == false){
                return false;
            }
        }
        if (currR != nullptr){
            R = currPaths(curr->right, currTotal, total);
            if (R == false){
                return false;
            }
        }
        return true;
    }else{
        if (total == 0){
            total = currTotal;
            return true;
        }else{
            if(total != currTotal){
                return false;
            }else{
                return true;
            }
        }
    }
}



bool equalPaths(Node * root)
{
    Node* curr = root;
    int lenCurr = 0;
    int len = 0;

    if (root == NULL){
        return true;
    }

    bool res = currPaths(curr, lenCurr, len);
    return res;

}



