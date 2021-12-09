#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "my_kd_tree.h"

extern const int k{3};

// A node in the tree has 3 main elements: the data it carries, a pointer to its left node, a pointer to its right node
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

// recursively insert node to construct the kd-tree
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

// determine if two Points are same
bool arePointsSame(std::vector<double> point1, std::vector<double> point2)
{
    for (int i = 0; i < k; ++i)
    {
         if (point1[i] != point2[i])
         {
            return false;
         }   
    }
    return true;
}


// search if the node exists in the tree
bool search(Node *root, std::vector<double> search_point, unsigned depth)
{
    if (root == NULL)
    {
        // std::cout << "No tree available!" << std::endl;
        return false;
    }
    if (arePointsSame(root->point, search_point))
    {
        // std::cout << "Found point: " << root->point << std::endl;
        return true;
    }

    // get current dimension
    unsigned cd = depth % k;

    // compare point with root on current dimension
    // if search_point[cd] smaller than current_node[cd], then go left and keep searching
    if (search_point[cd] < root->point[cd])
    {
        return search(root->left, search_point, depth + 1);
    }
    // if search_point[cd] bigger than current_node[cd], then go right and keep searching
    return search(root->right, search_point, depth + 1);
}


// visualize the kd-tree
void print_vector(std::vector<double> Vector){
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

void print_kd_tree(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != NULL )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        print_vector(node->point);
        // enter the next tree level - left and right branch
        print_kd_tree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_kd_tree( prefix + (isLeft ? "│   " : "    "), node->right, false);
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


Node *delete_node(std::vector<std::vector<double>> &value_vecs, std::vector<double> point_to_delete)
{
    // we delete the point from the vector of vectors, then reconstruct the tree
    value_vecs.erase(std::remove(value_vecs.begin(), value_vecs.end(), point_to_delete), value_vecs.end());

    Node *new_root = NULL;
    for (auto &elem : value_vecs)
    {
        new_root = insert(elem, new_root);
    }
    return new_root;
}