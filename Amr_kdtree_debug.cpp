#include <iostream>
#include<iterator>
#include<algorithm>
#include<string>
#include <vector>

const int k{3};

std::ostream& operator<<(std::ostream& os, std::vector<double> vec)
{
    for(const auto& elem : vec)
    {
        os << elem << " " ;
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
            std::cout << element << ", ";
        }
        std::cout << "\n";
    }
}

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

Node *insert(std::vector<double> &x, Node *parent, unsigned int cd=0)
{

    if (parent == NULL)
    {
        Node *parent = new Node(x);
        std::cout << "successfully created root: " << parent->point << std::endl;
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



class Utilities
{
    // A class of utility functions 
public:
    bool arePointsSame(std::vector<double> point1, std::vector<double> point2)
    // determine if two Points are same
    {
        for (int i = 0; i < k; ++i)
            if (point1[i] != point2[i])
                return false;

        return true;
    }

    bool search(Node* root, std::vector<double> point, unsigned depth=0)
    {
    // search if the point exists in the KD-tree
        if (root == NULL)
            return false;
        if (arePointsSame(root->point, point))
            return true;

        // Current dimension is computed using current depth and total
        // dimensions (k)
        unsigned cd = depth % k;

        // Compare point with root with respect to cd (Current dimension)
        if (point[cd] < root->point[cd])
            return search(root->left, point, depth + 1);

        return search(root->right, point, depth + 1);
    }

};



int main()
{
    Node *root = NULL;
    
    auto value_vectors = generate_numbers(100);
    // print_array(value_vectors);

    Utilities utils;
    for (auto &elem : value_vectors)
    {
        root = insert(elem, root);
    }

    std::vector<double> point1 = value_vectors[0];
	(utils.search(root, point1))? std::cout << "Found\n": std::cout << "Not Found\n";

    delete root;



    // create_csv_Tree(value_vectors);
    // Node root(value_vectors[0]);
    // visualize_tree(root);
    // generate_csv();
}