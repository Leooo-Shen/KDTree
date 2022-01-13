#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include "my_kd_tree.h"


std::string filepath = "../data/generated_values.csv";

int main()
{
    Node *root = NULL;

    auto value_vectors =generate_numbers(100);

    write_to_csv(value_vectors, filepath);

    for (auto &elem : value_vectors)
    {
        root = insert(elem, root);
    }
    print_kd_tree("",root,false);

}