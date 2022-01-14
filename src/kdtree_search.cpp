#include <stack>
#include "my_kd_tree.h"
#include <math.h>
#include <string>

double distance(std::vector<double> a, std::vector<double> b)
{
    double dist = 0;
    for (unsigned i=0; i < a.size(); i++)
    {
        dist += pow((a[i] - b[i]),2);
    }
    return sqrt(dist);
}


// input:constructed tree, target point
// return: nearest neighbor of target
std::vector<double> searchNN(Node *root, std::vector<double> target)
{

    /*
    To find Nearest Neighbor:

    Step 1: 
        Recursively search down the tree: 
        - If target[cd] < nodePoint[cd]: go to its left child node;
        - If target[cd] >= nodePoint[cd]: go to its right child node
        - Stop until a leaf node. Assign this node as current_NN.

    Step 2: 
        Climb back from the leaf node and search for potential NN:
        - computer current_dist = dist(target, current_NN)
        - check another side of the parent node for potential NN (e.g if current is parent's left/right node, check parent's right/left node)
          We can 
    
    */

    unsigned depth = 0;
    unsigned dim = root->point.size();  // dimension of the data point （x,y,z）

    Node* currentNode = root;
    std::vector<double> currentNN = currentNode->point;

    while(!currentNode->isLeaf())
    {
        // current dimension
        // !!!!!!!!!!!!! TODO: Segmentation Error!!!!!!!!!
        unsigned cd = depth % dim;
        std::cout << "  cd: " << cd << "  target: " << target[cd]  << "  currentNN: " << currentNN[cd] << std::endl;

        if(currentNode->right->point.empty() || target[cd] < currentNN[cd])
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
    print_vector(currentNN);

    // auto current_dist = distance(currentNN, target);

    // // Now we need to check for potential NN
    // Node* potential_NN;

    // if (currentNode->isLeftChild())
    // {   // if current node is the left child, then search for parent's right child
    //     if (currentNode->parent->right == nullptr)
    //     {
    //         potential_NN = currentNode; 
    //     }
    //     else
    //     {
    //         potential_NN = currentNode->parent->right;
    //     }
    // }
    // else
    // {
    //     potential_NN = currentNode->parent->left;
    // }

    // // while not reaching the tree root, keeps climbing up
    // while (potential_NN->parent != nullptr)
    // {
    //     // if dist(current_NN, target) >  dist(potential_NN[cd], target[cd])
    //     // then in the other subspace(the other side of the parent) may have true NN
    //     unsigned cd = depth % dim;
    //     auto dist_to_edge = abs(potential_NN->parent->point[cd] - target[cd]);

    //     if (current_dist > dist_to_edge)
    //     {
    //         auto potential_dist = distance(potential_NN->point, target);

    //         if (potential_dist < current_dist)
    //         {
    //             current_dist = potential_dist;
    //             currentNode = potential_NN->parent;
    //             currentNN = currentNode->point;
    //         }
    //         // if (!potential_NN->point.empty())
    //         // {
    //         //     auto rootDistance = distance(target, potential_NN->point);
    //         //     if (rootDistance < current_dist)
    //         //     {
    //         //         current_dist = rootDistance;
    //         //         currentNode = potential_NN;
    //         //         currentNN = currentNode->point;
    //         //     }
    //         // }
    //         if (potential_NN->left != NULL)
    //         {
    //             double leftDistance = distance(target, potential_NN->left->point);
    //             if (leftDistance < current_dist)
    //             {
    //                 current_dist = leftDistance;
    //                 currentNode = potential_NN;
    //                 currentNN = currentNode->point;
    //             }
    //         }
    //         if (potential_NN->right != NULL)
    //         {
    //             double rightDistance = distance(target, potential_NN->right->point);
    //             if (rightDistance < current_dist)
    //             {
    //                 current_dist = rightDistance;
    //                 currentNode = potential_NN;
    //                 currentNN = currentNode->point;
    //             }
    //         }
    //     }
    //     if (potential_NN->parent != nullptr)
    //     {
    //         if (potential_NN->parent->isLeftChild())
    //         {
    //             potential_NN = potential_NN->parent->parent->right;
    //         }
    //         else
    //         {
    //             potential_NN->parent->parent->left;
    //         }                     
    //     }
    //     else
    //     {
    //         potential_NN = potential_NN->parent;
    //     }
    //     ++depth;

    // }
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