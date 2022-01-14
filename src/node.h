#ifndef __NODE_H_
#define __NODE_H_

#include <vector>

// A node in the tree has 3 main elements: 
// the data it carries, a pointer to its left node, a pointer to its right node
struct Node
{
    std::vector<double> point;
    Node* left;
    Node* right;
    Node* parent;
    Node(std::vector<double> &Tpoint)
    {
        point = Tpoint;
        left = right = nullptr;
       
    }

    bool isRoot()
    {
        return {(!point.empty() && parent == nullptr)};
    }

    bool isLeaf()
    {
        return {(!point.empty()) && left == nullptr && right == nullptr};
    }

    bool isLeftChild()
    {
        return {parent->left->point == point};
    }

    bool isRightChild()
    {
        return {parent->right->point == point};
    }
};


#endif