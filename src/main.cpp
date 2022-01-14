#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "my_kd_tree.h"


void test_tree_construction()
{
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
    print_kd_tree("",root,false);
    std::cout << findMin(root, 0, 0) << std::endl;
    std::cout << findMin(root, 1, 0) << std::endl;
}


void test_findMin()
{
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
    if (root != NULL) {std::cout << "not empty root" << std::endl;}
    
    std::cout << findMin(root, 0, 0) << std::endl;
    std::cout << findMin(root, 1, 0) << std::endl;
}


int main()
{
    // std::string filepath = "../data/generated_values.csv";
    // Node *root = NULL;
    // std::vector<std::vector<double>> value_vectors;

    // // // generate toy data
    // // value_vectors =generate_numbers(100);

    // // // write generated data to csv
    // // write_to_csv(value_vectors, filepath);

    // // // read data as vector of vectors from csv file
    // try{

    //     value_vectors = read_from_csv(filepath);

    //      // construct the tree
    //     for (auto &elem : value_vectors)
    //     {
    //         root = insert(elem, root);
    //     }
    //     // std::cout << typeid(root).name() << std::endl;
    //     // if (root != NULL) {std::cout << "not empty root" << std::endl;}

    //     // print_kd_tree("",root,false);

    //     std::cout << findMin(root, 0, 0) << std::endl;
    //     std::cout << findMin(root, 1, 0) << std::endl;

    //     // Node *new_root = delete_node(value_vectors, value_vectors[0]);
    //     // print_kd_tree("",new_root,false);

    // }
    // catch(int){
    //     std::cout << "Cannot open the file. Check if the file exists!" << std::endl;
    // }

    test_tree_construction();
    // test_findMin();

    return 0;

}