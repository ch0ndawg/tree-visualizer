//
//  main.cpp
//  tree-visualizer
//
//  Created by Chris on 12/25/15.
//  Copyright © 2015 Chris. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

#include "avl-tree.h"
#include "plain-tree.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    AVLTree t;
    BSTree s;
    std::cout << "How many items in the tree? ";
    int N;
    std::cin >> N;
  //  std::cout << "Enter the items separated by whitespace:\n";
    for (int i=1; i<= N; i++) {
       // int x;
       // std::cin >> x;
        t.insert(i);
    }
    
    
    //srand(time(NULL));
    for (int i=1; i<= N; i++) {
        // int x;
        // std::cin >> x;
        s.insert(rand()%i);
    }
    
    std::vector<std::ostringstream> stringBufs(t.height());
    //std::ofstream outfile("outtree.txt", std::ios::ate);
    
    // find the maximum-sized integer
    std::ostringstream sizeFind;
    int maxVal = t.find_max();
    sizeFind << maxVal;
    
    // this multiplies the size of each displayed result in the line
    unsigned multiplier = 1+sizeFind.str().length();
    
    // largest number of items is the size of the largest level, 2^height
    int maxLine = multiplier*(1 << t.height());
    
    // level order traversal (the real way to do this is via a level order iterator
    for (int level=0; level < t.height(); level++) {
        unsigned numAtThisLevel = 1<<level; // number of entries at this level (including null)
        int width = maxLine>>level; // chop up the line into numAtThisLevel pieces
        for (int i = 0; i < numAtThisLevel; i++) {
            node *n = t.binary_index_unchecked(level, i); // get binary index node
        //    if (!n) std::cout  << t.binary_index(level,i);
            // temporary stopgap: the real way to do this is via a level order iterator
            std::ostringstream centered; // in order to center each number, set it left-justified at half the width
            //multiplier = 0;
            if (n) {
                // also adjust the half-width with half the "max size" width to center over the digit in the center (possibly one off)
                centered << std::setw((width+multiplier)/2) << std::left << n->val;
            }
            else { // use spaces for null
                centered << std::setw((width+multiplier)/2) << std::left << ' ';
            }
            // append it to the string bufffer with the full width
            stringBufs[level] << std::setw(width) << centered.str();
        }
        std::cout << stringBufs[level].str() << std::endl <<std::endl;
    }
    //t.level_order(std::cout);
    maxVal = s.find_max();
    sizeFind << maxVal;
    
    // this multiplies the size of each displayed result in the line
    multiplier = 1+sizeFind.str().length();
    
    // largest number of items is the size of the largest level, 2^height
    maxLine = multiplier*(1 << s.height());
    maxLine /=4;
    
    std::vector<std::ostringstream> stringBufs2(s.height());
    // level order traversal (the real way to do this is via a level order iterator
    for (int level=0; level < s.height(); level++) {
        unsigned numAtThisLevel = 1<<level; // number of entries at this level (including null)
        int width = maxLine>>level; // chop up the line into numAtThisLevel pieces
        for (int i = 0; i < numAtThisLevel; i++) {
            node *n = s.binary_index_unchecked(level, i); // get binary index node
            //    if (!n) std::cout  << t.binary_index(level,i);
            // temporary stopgap: the real way to do this is via a level order iterator
            std::ostringstream centered; // in order to center each number, set it left-justified at half the width
            //multiplier = 0;
            if (n) {
                // also adjust the half-width with half the "max size" width to center over the digit in the center (possibly one off)
                centered << std::setw((width+multiplier)/2) << std::left << n->val;
            }
            /*else { // use spaces for null
                centered << std::setw((width+multiplier)/2) << std::left << ' ';
            } */
            // append it to the string bufffer with the full width
            stringBufs2[level] << std::setw(width) << centered.str();
        }
        std::cout << stringBufs2[level].str() << std::endl <<std::endl;
    }

    return 0;
}
