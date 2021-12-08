#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "my_kd_tree.h"

extern const int k{3};

struct Node
{
    std::vector<double> point;
    Node *left;
    Node *right;
    Node(std::vector<double> &Tpoint)
    {
        point = Tpoint;
        left = right = NULL;
    }
};

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
    std::vector<std::vector<double>> generated_int(n, std::vector<double>(k, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            generated_int[i][j] = (rand() % 100);
        }
    }
    return generated_int;
}

void print_array(std::vector<std::vector<double>> generate_numbers)
{
    for (auto vectors : generate_numbers)
    {
        for (auto element : vectors)
        {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------" << std::endl;
    std::cout << "Total number of points: " << generate_numbers.size() << std::endl;
}

Node *insert(std::vector<double> &x, Node *parent, unsigned cd)
{

    if (parent == NULL)
    {
        Node *parent = new Node(x);
        // std::cout << "successfully created root: " << parent->point << std::endl;
        return parent;
    }
    else if (x == parent->point)
    { // error! duplicate
    }
    else if (x[cd] < parent->point[cd])
    {
        parent->left = insert(x, parent->left, (cd + 1) % k);
    }
    else
    {
        parent->right = insert(x, parent->right, (cd + 1) % k);
    }
    return parent;
}

bool arePointsSame(std::vector<double> point1, std::vector<double> point2)
// determine if two Points are same
{
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

bool search(Node *root, std::vector<double> point, unsigned depth)
{
    // search if the point exists in the KD-tree
    if (root == NULL)
    {
        // std::cout << "No tree available!" << std::endl;
        return false;
    }
    if (arePointsSame(root->point, point))
    {
        std::cout << root->point << std::endl;
        return true;
    }

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return search(root->left, point, depth + 1);

    return search(root->right, point, depth + 1);
}

// // A utility function to find minimum of three integers
// Node *minNode(Node *x, Node *y, Node *z, unsigned comparing_d)
// {
//     Node *res = x;
//     if (y != NULL && y->point[comparing_d] < res->point[comparing_d])
//         res = y;
//     if (z != NULL && z->point[comparing_d] < res->point[comparing_d])
//         res = z;
//     return res;
// }

// Node *findMin(Node *root, unsigned int comparing_d, unsigned depth)
// {
//     // Base cases
//     if (root == NULL)
//     {
//         // std::cout << "Tree is empty, cannot find min!" << std::endl;
//         return NULL;
//     }

//     // Current dimension
//     unsigned current_d = depth % k;

//     // Compare point with root with respect to cd (Current dimension)
//     if (current_d == comparing_d)
//     {
//         if (root->left == NULL)
//         {
//             return root;
//         }
//         else
//         {
//             return findMin(root->left, comparing_d, depth + 1);
//         }
//     }

//     // If current dimension is different then minimum can be anywhere
//     // in this subtree
//     return minNode(root,
//                    findMin(root->left, comparing_d, depth + 1),
//                    findMin(root->right, comparing_d, depth + 1), comparing_d);
// }

// // Function to delete a given point from K D Tree with 'root'
// Node *deleteNode(Node *root, std::vector<double> point, unsigned depth)
// {
//     // Given point is not present
//     if (root == NULL)
//         return NULL;

//     // Find dimension of current node
//     unsigned int cd = depth % k;

//     // If the point to be deleted is present at root
//     if (arePointsSame(root->point, point))
//     {
//         // 2.b) If right child is not NULL
//         if (root->right != NULL)
//         {
//             // Find minimum of root's dimension in right subtree
//             Node *min = findMin(root->right, cd);

//             // Copy the minimum to root
//             root->point = min->point;

//             // Recursively delete the minimum
//             root->right = deleteNode(root->right, min->point, depth + 1);
//         }
//         else if (root->left != NULL) // same as above
//         {
//             Node *min = findMin(root->left, cd);
//             root->point = min->point;
//             root->right = deleteNode(root->left, min->point, depth + 1);
//         }
//         else // If node to be deleted is leaf node
//         {
//             delete root;
//             return NULL;
//         }
//         return root;
//     }

//     // 2) If current node doesn't contain point, search downward
//     if (point[cd] < root->point[cd])
//         root->left = deleteNode(root->left, point, depth + 1);
//     else
//         root->right = deleteNode(root->right, point, depth + 1);
//     return root;
// }

void print_kd_tree(Node *tree, unsigned depth)
{
    for (unsigned i = 0; i < depth; ++i)
        std::cout << "\t";

    for (std::vector<double>::size_type j = 0; j < tree->point.size(); ++j)
        std::cout << tree->point[j] << ",";
    std::cout << std::endl;

    // if current node if the leaf, end print
    if (tree->left == NULL && tree->right == NULL)
        return;

    // if current node not the leaf
    else
    {
        if (tree->left != NULL)
        {
            for (unsigned i = 0; i < depth + 1; ++i)
                std::cout << "\t";
            std::cout << " left:";
            print_kd_tree(tree->left, depth + 1);
        }

        std::cout << std::endl;
        if (tree->right != NULL)
        {
            for (unsigned i = 0; i < depth + 1; ++i)
                std::cout << "\t";
            std::cout << "right:";
            print_kd_tree(tree->right, depth + 1);
        }
        std::cout << std::endl;
    }
}

void write_to_csv(std::vector<std::vector<double>> &generated_numbers,
                  std::string filename)
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

std::vector<std::vector<double>> read_from_csv(std::string filename)
{
    std::ifstream database(filename);
    std::vector<std::vector<double>> value_vectors;
    std::vector<double> point;
    double single_value;

    if (!database.is_open())
    {
        std::cout << "Cannot open the file." << std::endl;
    }

    std::string line;
    // throw away first line: contains csv header
    std::getline(database, line);

    // while lines in csv
    while (std::getline(database, line))
    {
        std::stringstream line_stream(line);
        while (line_stream >> single_value)
        {
            point.push_back(single_value);
        }
        value_vectors.push_back(point);
        point.clear();
    }

    database.close();
    return value_vectors;
}
