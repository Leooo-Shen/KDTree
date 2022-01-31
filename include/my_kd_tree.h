#ifndef __HELPER_H_
#define __HELPER_H_

#include "utils.h"


class KdTree
{
public:

    // return the dimension of data points in the tree
    unsigned dimension(Node* root);

    Node* insert(const std::vector<double> &x, Node* tree, unsigned cd);

    Node* construct(const std::vector<std::vector<double>> &value_vectors);

    bool exist(const Node* root);

    // delete one of the nodes from the tree
    Node* delete_single_node(std::vector<std::vector<double>> &origin_vecs, std::vector<double> point_to_delete);

    // search if the target node is inside the tree
    bool contain_node(Node *root, std::vector<double> search_point, unsigned depth = 0) const;

    // print tree structure
    void print_tree(const std::string& prefix, const Node* node, bool isLeft=false) const;

    // find the minimum of single given dimension
    double find_min(Node* root, unsigned desired_dim, unsigned depth=0) const;

    // a wrapper function of find_dim_min that returns the minimum value of all dimensions
    std::vector<double> find_min_all(Node* root, unsigned desired_dim, unsigned depth=0) const;

    //finds the nearest neighbour of a given target
    Node* searchNN(std::vector<double> Q, Node* Root, int cd, std::shared_ptr<Rect> BB) ;

    // free memories of all subtree rooted at current node
    void delete_tree(Node* current_node);

};


#endif
