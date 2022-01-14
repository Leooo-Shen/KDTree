#include <stack>
#include "my_kd_tree.h"
#include <math.h>
#include <string>

// double distance(std::vector<double> a, std::vector<double> b)
// {
//     double dist = 0;
//     for (unsigned i=0; i < a.size(); i++)
//     {
//         dist += pow((a[i] - b[i]),2);
//     }
//     return sqrt(dist);
// }


// input:constructed tree, target point
// return: nearest neighbor of target
std::vector<double> searchNN(Node *root, std::vector<double> target)
{
    unsigned depth = 0;
    unsigned dim = root->point.size();  // dimension of the point

    Node* currentNode = root;
    std::vector<double> currentNN = currentNode->point;
    if (currentNode != NULL) {std::cout << "not empty root" << std::endl;}

    while(!currentNode->isLeaf())
    {
        // current dimension
        unsigned cd = depth % dim;

        if(currentNode->right->isEmpty() || target[cd] < currentNN[cd])
        {
            currentNode = currentNode->left;
            std::cout << "searching left:" << std::endl;
            print_vector(currentNode->point);
        }
        else
        {
            currentNode = currentNode->right;
            std::cout << "searching right:" << std::endl;
            print_vector(currentNode->point);
        }
        ++depth;
    }
    currentNN = currentNode->point;

    return currentNN;
}


int main()
{
    Node *root = nullptr;
    auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
    for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
    print_kd_tree("",root,false);
    auto target = std::vector<double>{8,1.01};
    auto NN = searchNN(root, target);
    print_vector(NN);
}