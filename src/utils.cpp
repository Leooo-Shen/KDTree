#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "utils.h"
#include "node.h"
#include "my_kd_tree.h"


// Reload the << to ouput vectors more conviently
std::ostream &operator<<(std::ostream &os, std::vector<double> vec)
{
    
    for (const auto &elem : vec)
    {
        os << elem << " ";
    }
    os << '\n';
    return os;
}


std::vector<std::vector<double>> generate_numbers(int n)
{
    /*
    Generate fake data of k-dimensions;
    param:
        inputs: 
            n: total numbers of vectors want to generate (int)
        returns:
            generated_int: a general vector of generated value vectors (std::vector<std::vector<double>>)

    */
    srand(time(0));
    std::vector<std::vector<double>> generated_values(n, std::vector<double>(k, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            generated_values[i][j] = (double)rand()/RAND_MAX*300-150;
        }
    }
    return generated_values;
}


// visualize the kd-tree
void print_vector(const std::vector<double>& Vector){
    std::cout<<"[";
    std::string messy{""};
    for(auto elements: Vector){
            messy=messy+std::to_string(elements)+",";
    }
    messy.pop_back();
    std::cout<<messy;
    std::cout<<"]";
    std::cout<<std::endl;
}


void write_to_csv(const std::vector<std::vector<double>> &generated_numbers,
                  const std::string& filename)
{
    // open file stream for output
    std::ofstream csv_file(filename);

    // csv column headers
    csv_file << "generated k-dimension data, k = " << k << "\n";

    for (size_t i = 0; i < generated_numbers.size(); i++)
    {
        csv_file << generated_numbers[i];
    }
    csv_file.close();
}


std::vector<std::vector<double>> read_from_csv(const std::string& filename)
{
    std::ifstream ifs(filename);
    std::vector<std::vector<double>> value_vectors;
    std::vector<double> point;
    double single_value;
    std::cout << "opening the file: " << filename << std::endl;


    if (!ifs.is_open())
    {
        throw -1;
    }

    std::string line;
    // throw away first line: contains csv header
    std::getline(ifs, line);

    // while lines in csv
    while (std::getline(ifs, line))
    {
        std::stringstream line_stream(line);
        while (line_stream >> single_value)
        {
            point.push_back(single_value);
        }
        value_vectors.push_back(point);
        point.clear();
    }
    ifs.close();
    return value_vectors;
}


void test_tree_construction()
{
    KdTree kdtree;
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = kdtree.insert(elem, root, 0);
        }
    kdtree.print_tree("",root,false);

    kdtree.free_memory(root);
}


void test_find_min()
{
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

    kdtree.free_memory(root);
}
