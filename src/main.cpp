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
    auto value_vectors =generate_numbers(100);

    // // write generated data to csv
    write_to_csv(value_vectors, filepath);

    // read data as vector of vectors from csv file
    // auto value_vectors = read_from_csv(filepath);

    // print vectors
    // for (auto &elem : value_vectors)
    // {
    //     print_vector(elem);
    // }

    // construct the tree
    for (auto &elem : value_vectors)
    {
        root = insert(elem, root);
    }
    print_kd_tree("",root,false);

    // Node *new_root = delete_node(value_vectors, value_vectors[0]);
    // print_kd_tree("",new_root,false);
}