#include "../include/my_kd_tree.h"

void test_tree_construction()
{
    //Generate a tree based on preconceived data and print it (for testing);
    

    KdTree kdtree;
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = kdtree.insert(elem, root, 0);
        }
    kdtree.print_tree("",root,false);

    kdtree.delete_tree(root);
}


void test_find_min()
{
    
    //test for finding the minimum of a tree with preconcieved data 
    
    KdTree kdtree;
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = kdtree.insert(elem, root, 0);
        }
    if (root != NULL) {std::cout << "not empty root" << std::endl;}
    std::cout << kdtree.find_min(root, 0, 0) << std::endl;
    std::cout << kdtree.find_min(root, 1, 0) << std::endl;

    kdtree.delete_tree(root);
}
