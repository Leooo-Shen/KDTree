#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>

#define K 3


// reload << to better output vectors
std::ostream& operator<<(std::ostream& os, std::vector<double> vec)
{
    for(const auto& elem : vec)
    {
        os << elem << " " ;
    }
    os << '\n';
    return os;
}


// Each node in a KD-tree has: current node data, pointer to the left node, poiter to the right node
struct Node
{
    std::vector<double> point;
	Node *left;
    Node *right;
};


// create a new node 
Node* newNode(std::vector<double> in_arr)
{
	struct Node* new_node = new Node;
    new_node->point = in_arr;
	new_node->left = new_node->right = NULL;
    // std::cout << "in newNode: " << temp->point << std::endl;
	return new_node;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node* insert(Node *root, std::vector<double> point, unsigned int depth=0)
{
    // std::cout << "incoming new point: " << point << std::endl;
	// Tree is empty?
	if (root == NULL)
    {
        // std::cout << "Tree is empty, start constructing..." << std::endl;
    	return newNode(point);
    }
	// Calculate current dimension (cd) of comparison
	unsigned cd = depth % K;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[cd] < (root->point[cd]))
    {
        root->left = insert(root->left, point, depth + 1);
    }
	else
    {
        root->right = insert(root->right, point, depth + 1);
    }
	return root;
}

class Utilities
{
    // A class of utility functions 
public:
    bool arePointsSame(std::vector<double> point1, std::vector<double> point2)
    // determine if two Points are same
    {
        for (int i = 0; i < K; ++i)
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
        unsigned cd = depth % K;

        // Compare point with root with respect to cd (Current dimension)
        if (point[cd] < root->point[cd])
            return search(root->left, point, depth + 1);

        return search(root->right, point, depth + 1);
    }

};


int main()
{
	struct Node *root = NULL;
    Utilities utils;
	// std::vector<std::vector<double>> points_Arr = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
	// 				{9, 1}, {2, 7}, {10, 19}};

    std::vector<std::vector<double>> points_Arr = {{3, 6,1}, {17, 15,1}, {13, 15,1}, {6, 12,1}};

    auto n = points_Arr.size();

	for (int i=0; i<n; i++)
    {
        root = insert(root, points_Arr[i]);
    }

	std::vector<double> point1 = {3, 6,1};
	(utils.search(root, point1))? std::cout << "Found\n": std::cout << "Not Found\n";

	std::vector<double> point2 = {12, 19, 2};
	(utils.search(root, point2))? std::cout << "Found\n": std::cout << "Not Found\n";
    
    delete root;
	return 0;
}
