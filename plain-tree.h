//
//  plain-tree.h
//  tree-visualizer
//
//  Created by Chris on 12/26/15.
//  Copyright © 2015 Chris. All rights reserved.
//

#ifndef plain_tree_h
#define plain_tree_h
#include <iostream>
#include "avl-tree.h"

class BSTree {
    node *nullNode;
    node *root;
    void rec_insert(node* & curr, int val);
    void in_order(std::ostream&os, node* curr) const;
public:
    BSTree() : nullNode(new node), root(nullNode) { nullNode->left = nullNode->right = nullNode; nullNode->ht = 0;}
    BSTree(node *newRoot) : root(newRoot) {}
    BSTree(const BSTree&);
    BSTree & insert(int data);
    BSTree & remove(int data);
    const int & binary_index(int level, unsigned index) const; // level order indexing
    int & binary_index(int level, unsigned index)
    { return const_cast<int&>(static_cast<const BSTree&>(*this).binary_index(level, index)); } // Meyers p.
    node *binary_index_unchecked(int level, unsigned index) const;
    void in_order(std::ostream& os) const { in_order (os,root); }
    void level_order(std::ostream&os) const;
    int height() const { return root->ht;}
    int find_max() const;
    class item_not_found {};
};

inline std::ostream &operator <<(std::ostream& os, const BSTree& t)
{ t.in_order(os); return os; }


#endif /* plain_tree_h */
