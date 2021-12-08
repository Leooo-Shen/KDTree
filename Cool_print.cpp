#include<iostream>
#include<fstream>
#include<vector>

//Cool printing function to print AFTER FORMING TREE :) !!
const int k{3};
struct Node{
    std::vector<int> point;
    Node * left=NULL;
    Node * right=NULL;
    Node(std::vector<int> Tpoint){
         point=Tpoint;
        
        left=right=NULL;
    }
};
void print_vector(std::vector<int> Vector){
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

void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != NULL )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        print_vector(node->point);
        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}