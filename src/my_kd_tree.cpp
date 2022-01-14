#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "my_kd_tree.h"
#include "node.h"
#include "utils.h"

extern const int k{3};


// recursively insert node to construct the kd-tree
Node* KdTree::insert(std::vector<double> &x, Node* tree, unsigned cd)
{   
    if (tree == nullptr)
    {
        Node* tree = new Node(x);
        // unique_ptr<Node> tree = (x);

        // std::cout << "successfully created root: " << tree->point << std::endl;
        return tree;
    }
    else if (x == tree->point)
    { // error! duplicate
    }
    else if (x[cd] < tree->point[cd])
    {
        tree->left = insert(x, tree->left, (cd + 1) % k);
        Node* a;
        tree->parent = tree;
     }
    else
    {
        tree->right = insert(x, tree->right, (cd + 1) % k);
        tree->parent = tree;
    }
    return tree;
}


// search if the node exists in the tree
bool KdTree::contain_node(Node *root, std::vector<double> search_point, unsigned depth) const
{
    if (root == nullptr)
    {
        // std::cout << "No tree available!" << std::endl;
        return false;
    }
    if (root->point == search_point)
    {
        // std::cout << "Found point: " << root->point << std::endl;
        return true;
    }

    // get current dimension
    unsigned cd = depth % k;

    // compare point with root on current dimension
    // if search_point[cd] smaller than current_node[cd], then go left and keep searching
    if (search_point[cd] < root->point[cd])
    {
        return contain_node(root->left, search_point, depth + 1);
    }
    // if search_point[cd] bigger than current_node[cd], then go right and keep searching
    return contain_node(root->right, search_point, depth + 1);
}


void KdTree::print_tree(const std::string& prefix, const Node* node, bool isLeft) const
{
    if( node != NULL )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        print_vector(node->point);
        // enter the next tree level - left and right branch
        print_tree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_tree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}


Node* KdTree::delete_node(std::vector<std::vector<double>> &value_vecs, std::vector<double> point_to_delete)
{
    // we delete the point from the vector of vectors, then reconstruct the tree
    value_vecs.erase(std::remove(value_vecs.begin(), value_vecs.end(), point_to_delete), value_vecs.end());
    Node *new_root = NULL;
    for (auto &elem : value_vecs)
    {
        new_root = insert(elem, new_root, 0);
    }
    return new_root;
}


// given the constructed tree, find the min node in corresponding dimension
double KdTree::find_min(Node* root, int desired_dim, unsigned depth) const
{
    //  Base cases
    if (root == NULL)
    {
        // std::cout << "Empty tree!" << std::endl;
        return -1;
    }
        
  
    // computer current dimension
    unsigned cd = depth % k;
  
    // if current_dim = desired dim:
    //      if current node has no left leaf --> current node is the minimum, return current node
    //      if current node still has left leaf --> go left and recursively search for the min. Then compare the found min with current node.
    if (cd == desired_dim) 
    {
        if (root->left == nullptr)
        {
            // print_vector(root->point);
            return root->point[desired_dim];
        }
        return std::min(root->point[desired_dim], find_min(root->left, desired_dim, depth + 1));
    }
    
  
    // if current_dim != disired dim, then the minimum can be anywhere in the tree. 
    // recursively goes left and right to search for the min. Then compare them with current node for the actual min.
    else
    {
        return std::min(root->point[desired_dim], 
                std::min(find_min(root->left, desired_dim, depth + 1),
                    find_min(root->right, desired_dim, depth + 1)));
    }

}

void KdTree::free_memory(Node* current_node)
{
    if (current_node == nullptr) return;
    free_memory(current_node->left);
    free_memory(current_node->right);
    delete current_node;
}

// KdTree::~KdTree()
// {
//     free_memory(root);
// }


// std::vector<double> KdTree::nearest_neighbor(Node* root, std::vector<double> target)
// {
//     // TODO
// }