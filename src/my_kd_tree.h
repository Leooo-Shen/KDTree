#ifndef __HELPER_H_
#define __HELPER_H_
#include <iostream>
#include <string>
#include <vector>
#include<fstream>

#include "node.h"

extern const int k;


class KdTree
{
public:

    // KdTree();

    // KdTree(Node* root)
    // {
    //     _root = root;
    // }

    // return the dimension of data points in the tree
    unsigned dimension() const;

    Node* insert(std::vector<double> &x, Node* tree, unsigned cd);

    // delete one of the nodes from the tree
    Node* delete_node(std::vector<std::vector<double>> &origin_vecs, std::vector<double> point_to_delete);

    // search if the target node is inside the tree
    bool contain_node(Node *root, std::vector<double> search_point, unsigned depth = 0) const;

    // print tree structure
    void print_tree(const std::string& prefix, const Node* node, bool isLeft) const;


    // find the minimum of given dimension
    double find_min(Node* root, int d, unsigned depth) const;

    //finds the nearest neighbour of a given target
    std::vector<double> nearest_neighbor(Node* root, std::vector<double> target) const;

    // free memories of all subtree rooted at current node
    void free_memory(Node* current_node);

    // // destruct the tree
    // ~KdTree();

// private:
//     struct Node
//     {
//         std::vector<double> point;  // data
//         Node* left;  // pointer to the left child
//         Node* right;  // pointer to the right child
//         Node* parent; // pointer to current_node's parent_node, nullptr if current_node is the root

//         Node(const std::vector<double> &_point):
//         point(_point), left(nullptr), right(nullptr), parent(nullptr){}
//     };
};


#endif
