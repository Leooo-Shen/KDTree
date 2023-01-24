#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include<fstream>
#include "my_kd_tree.h"



int main()
{
    std::string filepath = "../data/generated_values.csv";
    Node *root = NULL;
    std::vector<std::vector<double>> value_vectors;

    // generate toy data
    value_vectors =generate_numbers(100);

    // // write generated data to csv
    write_to_csv(value_vectors, filepath);

    // // read data as vector of vectors from csv file
    try{
        value_vectors = read_from_csv(filepath);

         // construct the tree
        for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
        print_kd_tree("",root,false);

        // Node *new_root = delete_node(value_vectors, value_vectors[0]);
        // print_kd_tree("",new_root,false);

    }
    catch(int){
        std::cout << "Cannot open the file. Check if the file exists!" << std::endl;
    }

    return 0;

}