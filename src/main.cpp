#include <iostream>
#include<iterator>
#include<algorithm>
#include<string>
#include <vector>

#include "my_kd_tree.h"


// void generate_csv()
// {
//     std::ofstream write_csv_file("./test_numbers1.csv");
//     write_csv_file << "x,y,z\n";
//     for (int i = 0; i < 100; i++)
//     {
//         std::string n1 = std::to_string(rand() % 100) + ",";
//         std::string n2 = std::to_string(rand() % 100) + ",";
//         std::string n3 = std::to_string(rand() % 100) + "\n";
//         write_csv_file << n1 + n2 + n3;
//     }
//     write_csv_file.close();
// }

// std::vector<std::vector<int>> convert_csv(std::string filename)
// {
//     std::ifstream read_csv_file;
//     read_csv_file.open(filename);
//     std::vector<std::vector<std::string>> converted_array;
//     std::vector<std::vector<int>> converted_int_array;
//     for (int i = 0; read_csv_file.good(); i++)
//     {
//         std::getline(read_csv_file, converted_array[i][0], ',');
//         converted_int_array[i][0] = std::stoi(converted_array[i][0]);
//         std::getline(read_csv_file, converted_array[i][1], ',');
//         converted_int_array[i][0] = std::stoi(converted_array[i][1]);
//         std::getline(read_csv_file, converted_array[i][2], ',');
//         converted_int_array[i][0] = std::stoi(converted_array[i][2]);
//     }
//     read_csv_file.close();
//     return converted_int_array;
// }

// void create_csv_Tree(std::vector<std::vector<int>> convert_csv)
// {
//     Node *root;
//     for (int i = 0; i < convert_csv.size(); i++)
//     {
//         insert(convert_csv[i], root, 0);
//     }
//     // we want to read from test_numbers and add nodes iteratively
// };


// void visualize_tree(Node* parent)
// {
//     // can make a local function here
//     std::cout << "[";
//     for (int i = 0; i < parent->point.size(); i++)
//     {
//         std::cout << parent->point[i] <<  ",";
//     }
//     std::cout << "]\n";
//     if (parent->left != NULL)
//     {

//         visualize_tree(parent->left);
//     }
//     if (parent->right != NULL)
//     {
//         std::cout << "             ";
//         visualize_tree(parent->right);
//     }
// }


int main()
{
    Node *root = NULL;
    
    auto value_vectors = generate_numbers(100);
    // print_array(value_vectors);

    for (auto &elem : value_vectors)
    {
        root = insert(elem, root);
    }

    std::vector<double> point1 = value_vectors[0];
	(search(root, point1))? std::cout << "Found\n": std::cout << "Not Found\n";

    root = deleteNode(root, point1);
    (search(root, point1))? std::cout << "Found\n": std::cout << "Not Found\n";

    // create_csv_Tree(value_vectors);
    // Node root(value_vectors[0]);
    // visualize_tree(root);
    // generate_csv();
}