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
    std::cout << "#####################################################" << std::endl;
    std::cout << "##  Welcome to Amr and Chengzhi's KD-Tree project! ##" << std::endl;
    std::cout << "#####################################################" << std::endl;
    std::cout << std::endl;

    std::cout << "Please choos the input mode:" << std::endl;
    std::cout << "(case 0) use your own .csv data file " << std::endl;
    std::cout << "(case 1) generate random data " << std::endl;

    std::string filepath;
    std::vector<std::vector<double>> value_vectors;
    unsigned input_mode;
    std::cin >> input_mode;

    switch (input_mode)
    {
    case 0:
        std::cin >> filepath;
        break;

    case 1:
        filepath = "../data/generated_values_small.csv";
        value_vectors = generate_numbers(1000, k);
        write_to_csv(value_vectors, filepath);
        break;

    default:
        std::cout << "Invalid input!" << std::endl;
        break;
    }

    value_vectors = read_from_csv(filepath);
    auto dim = value_vectors[0].size();  // the dimension of the value vectors    
    KdTree kdtree;

    // construct the tree
    auto tree_root = kdtree.construct(value_vectors);
    if (kdtree.exist(tree_root))
    {
        std::cout << "Successfully constructed the tree!" << std::endl;
    }

    std::cout << std::endl
              << "Do you want to print the tree structure?" << std::endl;
    std::cout << "(case 0) yes " << std::endl;
    std::cout << "(case 1) no " << std::endl;
    unsigned print_case;
    std::cin >> print_case;

    switch (print_case)
    {
    case 0:
        kdtree.print_tree("", tree_root);
        break;

    default:
        break;
    }

    std::cout << std::endl;
    std::cout << "Choose the search strategy" << std::endl;
    std::cout << "(case 0) find minimum value " << std::endl;
    std::cout << "(case 1) find nearest neighbor " << std::endl;

    unsigned search_mode;
    std::cin >> search_mode;
    std::vector<double> min_values;
    double tmp; 
    std::vector<double> Target;  // your target point to find its nearest neighbor
    Node* NN;  // nearest neighbor

    std::shared_ptr<Rect> init_rect(new Rect(0, 0, 100, 100)); // a Rect is used during NN search. See Rect.h and my_kd_tree.cpp for more details

    switch (search_mode)
    {
    case 0:
        // find minimum value of all dimensions
        min_values = kdtree.find_min_all(tree_root);
        break;

    case 1:
        std::cout << "Please input your target point: " << std::endl;
        for (unsigned i = 0; i < dim; i++)
        {
            std::cout << "dimension " << i << ":";
            std::cin >> tmp;
            Target.push_back(tmp);
        }


        NN = kdtree.searchNN(Target, tree_root, 0, init_rect);
        std::cout << std::endl
                  << "Nearest Neighbor:  ";
        print_vector(NN->point);
        break;

    default:
        std::cout << "Invalid input!" << std::endl;
        break;
    }

    // delete the tree to free memory
    kdtree.delete_tree(tree_root);

    return 0;
}