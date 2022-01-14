#include<iostream>
#include<math.h>
#include "my_kd_tree.h"
auto value_vectors = std::vector<std::vector<double>> {{7,2}, {5,4}, {9,6}, {2,3}, {4,7}, {8,1}};
double distance(std::vector<double> A, std::vector<double> B){
    double dist = 0;
    for (unsigned i=0; i < A.size(); i++)
    {
        dist += pow((A[i] - B[i]),2);
    }
    return sqrt(dist);
}
double best_dist=-1;

Node* searchNN(std::vector<double> Q, Node* Root, int cd=0)
{
    Node* best=nullptr;
    if(best_dist==-1){
        Node* currentNode= insert(Q,Root,0);
        print_kd_tree("",currentNode,false);
        //inserted query point to find initial best estimate"
        auto catchv=0;
        while(!currentNode->isLeaf())
        {
            catchv++;
            if(Q[cd]<currentNode->point[cd]){
                best=currentNode;
                currentNode= currentNode->left;
            }
            else{best=currentNode;
                currentNode= currentNode->right; }
            // std::cout<<currentNode->isLeaf();
            
        }
        best_dist= distance(Q, best->point);
        std::cout<<best_dist;
        Root= delete_node(value_vectors, Q);
        return best;
    }
    //Now we check neighboring pixels :)


    return best;
}

int main()
{
    Node *root = nullptr;
    
    for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
    print_kd_tree("",root,false);
    auto target = std::vector<double>{8,1.01};
    auto NN = searchNN(target, root);
    print_vector(NN->point);
}