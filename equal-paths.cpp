#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool help(Node * nood, int& count) {
    if(nood == nullptr) {
        return true;
    }
    int migikaunto=0;
    int hidarikaunto=0;
    bool hidari = help(nood->left, hidarikaunto);
    bool migi = help(nood->right, migikaunto);
    if (hidari && migi) {
        if(migikaunto==hidarikaunto || nood->left == nullptr || nood->right == nullptr) {
            if(hidarikaunto >= migikaunto) {
                count = hidarikaunto + 1;
                return true;
            }
            else {
                count = migikaunto + 1;
                return true;
            }
        }
        else {
            return false;
        }
    } 
    else {
        return false;
    }
    return false;
}

bool equalPaths(Node * root)
{
    // Add your code below
    int count =0;
    return help(root, count);
}

