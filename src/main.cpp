#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <ctime>

#include "my_kd_tree.h"
#include "utils.h"
#include "searchNN.h"

// Create a k-dimention Node.
// In case of k = 2, there will be 2-d data in the Node (e.g (x, y) )
extern const int k{2};

int main()
{

    std::string filepath = "../data/generated_values.csv";
    KdTree kdtree;
    Node* root = nullptr;
    std::vector<std::vector<double>> value_vectors;

    // generate toy data
    // value_vectors = generate_numbers(100);

    // write generated data to csv
    // write_to_csv(value_vectors, filepath);

    // read data as vector of vectors from csv file
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


    std::vector<double> Target= {102,46};
    Rect* newrect=new Rect(0,0,100,100);
    Node* NN=kdtree.searchNN(Target, root,0, newrect);
    
    std::cout<<"final best: ";
    print_vector(NN->point);
    // kdtree.print_tree("",root,false);


    // kdtree.free_memory(root); 


    return 0;

}