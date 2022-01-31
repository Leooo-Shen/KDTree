#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <memory>

#include "../include/my_kd_tree.h"

// Create a k-dimention Node.
// In case of k = 2, there will be 2-d data in the Node (e.g (x, y) )
extern const int k{2};

int main()
{

    std::string filepath = "../data/generated_values.csv";
    KdTree kdtree;
    std::vector<std::vector<double>> value_vectors;

    // generate toy data
    value_vectors = generate_numbers(100);

    // write generated data to csv
    write_to_csv(value_vectors, filepath);

    // read data as vector of vectors from csv file
    value_vectors = read_from_csv(filepath);

    // construct the tree
    auto tree_root = kdtree.construct(value_vectors);

    // print constructed tree
    kdtree.print_tree("", tree_root);

    // find minimum value in respect of each dimension
    auto min_values = kdtree.find_min_all(tree_root, 0);


    // set a target to find its nearest neighbor
    std::vector<double> Target = {4, 32};

    // std::unique_ptr<Rect> newrect (new Rect(0, 0, 100, 100));
    Rect *newrect = new Rect(0, 0, 100, 100); 
    Node *NN = kdtree.searchNN(Target, tree_root, 0, newrect);

    std::cout << "Nearest Neighbor:  ";
    print_vector(NN->point);

    // delete the tree to free memory
    kdtree.delete_tree(tree_root);

    return 0;
}