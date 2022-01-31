#ifndef __HELPER_H_
#define __HELPER_H_
#include <iostream>
#include <string>
#include <vector>
#include<fstream>

#include "node.h"
#include "searchNN.h"

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
    Node* searchNN(std::vector<double> Q, Node* Root, int cd,Rect* BB) ;

    // free memories of all subtree rooted at current node
    void free_memory(Node* current_node);

    // // destruct the tree
    // ~KdTree();
};


#endif
