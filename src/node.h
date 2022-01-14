#ifndef __NODE_H_
#define __NODE_H_

#include <vector>

// A node in the tree has 3 main elements: 
// the data it carries, a pointer to its left node, a pointer to its right node
struct Node
{
    std::vector<double> point;
    Node *left;
    Node *right;
    Node(std::vector<double> &Tpoint)
    {
        point = Tpoint;
        left = right = nullptr;
    }

    bool isEmpty()
    {
        return point.empty();
    }
    
    bool isLeaf()
    {
        return (!point.empty()) && left == nullptr && right == nullptr;
    }
};


#endif