#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool help(Node * nood, int& count) { // made this so that I could actually use a counter
    if(nood == nullptr) { // handles the case where the node is null
        return true;
    }
    int migikaunto=0; // counter for the right tree
    int hidarikaunto=0; // counter for the left tree
    bool hidari = help(nood->left, hidarikaunto); // recursive call for the left tree
    bool migi = help(nood->right, migikaunto); // recursive call for the right tree
    if (hidari && migi) { // only runs if both left and right subtrees are equal because it will not be equal if they are not
        if(migikaunto==hidarikaunto || nood->left == nullptr || nood->right == nullptr) { //this checks the height of the two subtrees and compares them
            if(hidarikaunto >= migikaunto) {
                count = hidarikaunto + 1; // increases the left count by 1 to include the node being checked
                return true;
            }
            else {
                count = migikaunto + 1; //increases the right count by 1 to include the node being checked
                return true;
            }
        }
        else { // handles the case where the subtrees do not have the same height and are not null
            return false;
        }
    } 
    else { // handles the ase where the subtrees are not equal
        return false;
    }
    return false;
}

bool equalPaths(Node * root)
{
    // Add your code below
    int count =0;
    return help(root, count); // call to another recursive function that tracks the count which is the height
}

