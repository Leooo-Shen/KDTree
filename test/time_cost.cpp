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
    clock_t programStart = clock();

    // std::string filepath = "../data/generated_values_large.csv";  // 10 million
    // std::string filepath = "../data/generated_values_middle.csv";  // 1 million
    std::string filepath = "../data/generated_values_small.csv";  // 1k

    KdTree kdtree;
    std::vector<std::vector<double>> value_vectors;

    // value_vectors = generate_numbers(1000, 2);
    // write_to_csv(value_vectors, filepath);

    value_vectors = read_from_csv(filepath);

    auto tree_root = kdtree.construct(value_vectors);

    std::cout << std::endl;
    auto min_values = kdtree.find_min_all(tree_root, 0);

    // set a target to find its nearest neighbor
    std::vector<double> Target = {1, 2};

    clock_t startTime = clock();
    std::shared_ptr<Rect> newrect(new Rect(0, 0, 100, 100));
    auto NN = kdtree.searchNN(Target, tree_root, 0, newrect);
    clock_t endTime = clock();

    std::cout << "Nearest Neighbor:  ";
    print_vector(NN->point);
    std::cout << "[Time cost in searchNN: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s]" << std::endl;

    // delete the tree to free memory
    clock_t startTime2 = clock();
    kdtree.delete_tree(tree_root);
    clock_t endTime2 = clock();
    std::cout <<"[Time cost in delete_tree: " << double(endTime2 - startTime2) / CLOCKS_PER_SEC << "s]" << std::endl;


    clock_t programEnd = clock();

    std::cout << "[Total time: " << double(endTime2 - startTime2) / CLOCKS_PER_SEC << "s]" << std::endl;
    return 0;
}