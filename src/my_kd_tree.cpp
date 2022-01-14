#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "my_kd_tree.h"
#include "node.h"

extern const int k{3};


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
Node *insert(std::vector<double> &x, Node* tree, unsigned cd)
{   
    if (tree == nullptr)
    {
        //TODO: handle memeory leakage
        Node* tree = new Node(x);
        tree->left=nullptr;
        tree->right=nullptr;
        // unique_ptr<Node> tree = (x);
        tree->parent = tree;

        // std::cout << "successfully created root: " << tree->point << std::endl;
        return tree;
    }
    else if (x == tree->point)
    { // error! duplicate
    }
    else if (x[cd] < tree->point[cd])
    {
        tree->left = insert(x, tree->left, (cd + 1) % k);
    }
    else
    {
        tree->right = insert(x, tree->right, (cd + 1) % k);
    }
    return tree;
}


// search if the node exists in the tree
bool search(Node *root, std::vector<double> search_point, unsigned depth)
{
    if (root == nullptr)
    {
        // std::cout << "No tree available!" << std::endl;
        return false;
    }
    if (root->point == search_point)
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



// given the constructed tree, find the min node in corresponding dimension
double findMin(Node* root, int desired_dim, unsigned depth)
{
    //  Base cases
    if (root == NULL)
    {
        std::cout << "Empty tree!" << std::endl;
        return -1;
    }
        
  
    // computer current dimension
    unsigned cd = depth % k;
  
    // if current_dim = desired dim:
    //      if current node has no left leaf --> current node is the minimum, return current node
    //      if current node still has left leaf --> go left and recursively search for the min. Then compare the found min with current node.
    if (cd == desired_dim) 
    {
        if (root->left == nullptr)
        {
            // print_vector(root->point);
            return root->point[desired_dim];
        }
        return std::min(root->point[desired_dim], findMin(root->left, desired_dim, depth + 1));
    }
    
  
    // if current_dim != disired dim, then the minimum can be anywhere in the tree. 
    // recursively goes left and right to search for the min. Then compare them with current node for the actual min.
    else
    {
        return std::min(root->point[desired_dim], 
                std::min(findMin(root->left, desired_dim, depth + 1),
                    findMin(root->right, desired_dim, depth + 1)));
    }

}

