#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include<fstream>
#include "my_kd_tree.h"


std::string filepath = "../data/generated_values.csv";

int main()
{
    Node *root = NULL;

    // generate toy data
    // auto value_vectors = generate_numbers(5);

    // // write generated data to csv
    // write_to_csv(value_vectors, filepath);

    // read data as vector of vectors from csv file
    // auto value_vectors = read_from_csv(filepath);

    std::vector<std::vector<double>> value_vectors {{7,2}, {5,4}, {2,3}, {4,7}, {9,6}, {8,1}};

    // print vectors
    // print_vec(value_vectors);

    // construct the tree
    for (auto &elem : value_vectors)
    {
        root = insert(elem, root);
    }
    print_kd_tree(root);

    // Node *new_root = delete_node(value_vectors, value_vectors[0]);
    // print_kd_tree(new_root);

    // // test functions
    // std::vector<double> point1 = value_vectors[0];
    // (search(root, point1)) ? std::cout << "Found\n" : std::cout << "Not Found\n";
    // print_kd_tree(root);
    

    // root = deleteNode(root, point1);
    // (search(root, point1)) ? std::cout << "Found\n" : std::cout << "Not Found\n";
    // printKdTree(root);
}