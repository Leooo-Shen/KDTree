#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "my_kd_tree.h"
#include "utils.h"



int main()
{
    std::string filepath = "../data/generated_values.csv";
    KdTree kdtree;
    Node* root = nullptr;
    std::vector<std::vector<double>> value_vectors;

    // // generate toy data
    // value_vectors = generate_numbers(100);

    // write generated data to csv
    // write_to_csv(value_vectors, filepath);

    // read data as vector of vectors from csv file
    try{

        value_vectors = read_from_csv(filepath);

         // construct the tree
        for (auto &elem : value_vectors)
        {
            root = kdtree.insert(elem, root, 0);
        }
        // std::cout << typeid(root).name() << std::endl;
        // if (root != NULL) {std::cout << "not empty root" << std::endl;}

        kdtree.print_tree("",root,false);
        std::cout << "The minimum of dimension 0 is: " << kdtree.find_min(root, 0, 0) << std::endl;
        std::cout << "The minimum of dimension 1 is: " << kdtree.find_min(root, 1, 0) << std::endl;

        // kdtree.print_tree("",root,false);

        // Node* new_tree = kdtree.delete_node(value_vectors, value_vectors[0]);
        // kdtree.print_tree("",new_tree,false);

        kdtree.free_memory(root); 
        // kdtree.free_memory(new_tree); 

    }
    catch(int){
        std::cout << "Cannot open the file. Check if the file exists!" << std::endl;
    }

    // test_tree_construction();
    // test_find_min();

    return 0;

}