//
//  plain-tree.cpp
//  tree-visualizer
//
//  Created by Chris on 12/26/15.
//  Copyright © 2015 Chris. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "plain-tree.h"


BSTree& BSTree::insert(int val)
{
    rec_insert(root,val);
    return *this;
}

//void in_order(node*);
//void in_order_bf(node*);

void BSTree::rec_insert(node*& curr, int val)
{
    if (curr == nullNode) {
        curr = new node(val, nullNode,nullNode); // use the constructor
        return;
    }

    if (curr->val > val) {
        rec_insert(curr->left,val);
        if (curr->left->ht >= curr->ht) // if height needs to be changed
            ++curr->ht;
    }
    else if (curr->val < val) {
        rec_insert(curr->right,val);
        if (curr->right->ht >= curr->ht)
            ++curr->ht;
    } else {
        return; // they are equal, so stop
    }
}

const int & BSTree::binary_index(int level, unsigned index) const
{
    node *curr = binary_index_unchecked(level, index);
    if (curr == nullNode) {
        throw item_not_found();
    }
    return curr->val;
}

node *BSTree::binary_index_unchecked(int level, unsigned index) const
{
    node *curr = root;
    unsigned mask = 1 << (level-1);
    for (int i=0; i< level; i++) {
        curr = index & mask ? curr->right : curr->left; // select the right or left depending on mask
        mask >>=1;
    }
    return curr == nullNode? nullptr : curr; // note: this has to be fixed -- obviously it's not unchecked if it's still using a conditional
}

//class unbalanced_exception{};

/*void in_order_bf(node* curr)
 {
 if (curr == nullNode) return;
 
 in_order_bf(curr->left);
 int leftHt=0, rightHt=0;
 if(curr->left) leftHt = curr->left->ht;
 if(curr->right) rightHt = curr->right->ht;
 std::cout << curr->val << "(BF=" << leftHt -rightHt << ") ";
 if (abs(leftHt-rightHt) > 1) throw unbalanced_exception();
 in_order_bf(curr->right);
 }
 */
void BSTree::level_order(std::ostream & os) const
{
    for (int level = 0; level < root->ht; level++) {
        for ( int i = 0; i < (1<<level); i++) {
            node *curr = binary_index_unchecked(level,i);
            if (curr) os << curr->val << ' ';
        }
    }
}

int BSTree::find_max() const
{
    node *n = binary_index_unchecked(0, 0);
    int maxVal=0;
    while (n != nullNode) {
        maxVal = n->val;
        n=n->right;
    }
    return maxVal;
}
