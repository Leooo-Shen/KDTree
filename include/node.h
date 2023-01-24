#ifndef __NODE_H_
#define __NODE_H_

#include <vector>

struct Node
{
    
    std::vector<double> point;  // data
    Node* left = nullptr;  // pointer to the left child
    Node* right= nullptr;  // pointer to the right child
    Node* parent= nullptr; // pointer to current_node's parent_node, nullptr if current_node is the root

    // constructor
    Node() {parent = left = right = nullptr;};
    Node(const std::vector<double> &Tpoint)
    {
        point = Tpoint;
        parent = left = right = nullptr;
    }

    bool isEmpty()
    {
        return point.empty();
    }

    bool isRoot()
    {
        return !point.empty() && parent == nullptr;
    }

    bool isLeaf()
    {
        return left == nullptr && right == nullptr;
    }

    bool isLeftChild()
    {
        return parent->left->point == point;
    }

    bool isRightChild()
    {
        return parent->right->point == point;
    }

};


#endif