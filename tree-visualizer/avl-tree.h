//
//  avl-tree.h
//  tree-visualizer
//
//  Created by Chris on 12/25/15.
//  Copyright © 2015 Chris. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <iostream>
struct node {
    int val;
    node* left;
    node* right;
    int ht;
    
    node(int v=0, node* l=nullptr, node*r = nullptr) : val(v), left(l), right(r), ht(1) {}
    //  node(const node& other) : val(other.val), left(nullNodePtr), right(nullNodePtr), ht(other.ht) {
    //      if (other.left != nullNodePtr) { left = new node(other.left); }
    //      if (other.right != nullNodePtr) { right = new node(other.right);  } // recursive call!
    //  }
    //node (node&& other) : val(other.val), left(other.left), right(other.right), ht(other.ht) { other.left = nullptr; other.right=nullptr;} // move semantics
    //private:
    // special private constructor that makes the null node once and for all
    //  class nullNodeType {};
    //node( nullNodeType nnt) : val(0), left(this), right(this), ht(0) {}
};

class AVLTree {
    node *nullNode;
    node *root;
    void rec_insert(node* & curr, int val);
    void in_order(std::ostream&os, node* curr) const;
public:
    AVLTree() : nullNode(new node), root(nullNode) { nullNode->left = nullNode->right = nullNode; nullNode->ht = 0;}
    AVLTree(node *newRoot) : root(newRoot) {}
    AVLTree(const AVLTree&);
    AVLTree & insert(int data);
    AVLTree & remove(int data);
    const int & binary_index(int level, unsigned index) const; // level order indexing
    int & binary_index(int level, unsigned index)
    { return const_cast<int&>(static_cast<const AVLTree&>(*this).binary_index(level, index)); } // Meyers p.
    node *binary_index_unchecked(int level, unsigned index) const;
    void in_order(std::ostream& os) const { in_order (os,root); }
    void level_order(std::ostream&os) const;
    int height() const { return root->ht;}
    int find_max() const;
    class item_not_found {};
};

inline std::ostream &operator <<(std::ostream& os, const AVLTree& t)
{ t.in_order(os); return os; }
#endif /* Header_h */
