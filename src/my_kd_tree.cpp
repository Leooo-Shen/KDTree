
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>

#include "../include/my_kd_tree.h"

extern const int k;

unsigned KdTree::dimension(Node *root)
{
    return root->point.size();
}

Node *KdTree::insert(const std::vector<double> &x, Node *tree, unsigned cd)
{

    // recursively insert node to construct the kd-tree
    /*
    Insert a new node to a tree, can be done recursively for a whole tree;
    param:
        inputs:
            x: vector of doubles to be inserted to the new node
            tree: direct parent of the node
            cd: hyperparamater used to alternate between different dimensions
        returns:
            pointer: returns pointer to the root of the tree

    */

    if (tree == nullptr)
    {
        Node *tree = new Node(x);
        // unique_ptr<Node> tree = (x);

        // std::cout << "successfully created root: " << tree->point << std::endl;
        return tree;
    }
    else if (x == tree->point)
    { // error! duplicate
    }
    else if (x[cd] < tree->point[cd])
    {
        tree->parent = tree;
        tree->left = insert(x, tree->left, (cd + 1) % k);
    }
    else
    {
        tree->parent = tree;
        tree->right = insert(x, tree->right, (cd + 1) % k);
    }
    return tree;
}

Node *KdTree::construct(const std::vector<std::vector<double>> &value_vectors)
{
    clock_t startTime = clock();
    Node *root = nullptr;

    for (auto &elem : value_vectors)
    {
        root = insert(elem, root, 0);
    }

    clock_t endTime = clock();
    std::cout << "constructing successful";
    std::cout << std::endl
              << "[Time cost in construct: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s]" << std::endl;
    return root;
}

bool KdTree::exist(const Node *root)
{
    if (root != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool KdTree::contain_node(Node *root, std::vector<double> search_point, unsigned depth) const
{

    // search if the node exists in the tree

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
        return contain_node(root->left, search_point, depth + 1);
    }
    // if search_point[cd] bigger than current_node[cd], then go right and keep searching
    return contain_node(root->right, search_point, depth + 1);
}

void KdTree::print_tree(const std::string &prefix, const Node *node, bool isLeft) const
{
    if (node != NULL)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        print_vector(node->point);
        // enter the next tree level - left and right branch
        print_tree(prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_tree(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

Node *KdTree::delete_single_node(std::vector<std::vector<double>> &value_vecs, std::vector<double> point_to_delete)
{
    // we delete the point from the vector of vectors, then reconstruct the tree
    value_vecs.erase(std::remove(value_vecs.begin(), value_vecs.end(), point_to_delete), value_vecs.end());
    Node *new_root = NULL;
    for (auto &elem : value_vecs)
    {
        new_root = insert(elem, new_root, 0);
    }
    return new_root;
}

// given the constructed tree, find the min node in corresponding dimension
double KdTree::find_min(Node *root, unsigned desired_dim, unsigned depth) const
{
    //  Base cases
    if (root == NULL)
    {
        // std::cout << "Empty tree!" << std::endl;
        return 0;
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
        return std::min(root->point[desired_dim], find_min(root->left, desired_dim, depth + 1));
    }

    // if current_dim != disired dim, then the minimum can be anywhere in the tree.
    // recursively goes left and right to search for the min. Then compare them with current node for the actual min.
    else
    {
        return std::min(root->point[desired_dim],
                        std::min(find_min(root->left, desired_dim, depth + 1),
                                 find_min(root->right, desired_dim, depth + 1)));
    }
}

std::vector<double> KdTree::find_min_all(Node *root) const
{

    clock_t startTime = clock();
    auto point_dim = root->point.size();
    std::vector<double> min_values;

    for (unsigned desired_dim = 0; desired_dim < point_dim; desired_dim++)
    {
        auto curren_min = find_min(root, desired_dim);
        min_values.push_back(curren_min);

        std::cout << "Min of dimension " << desired_dim << ": " << curren_min << std::endl;
    }

    clock_t endTime = clock();
    std::cout << "[Time cost in find_min: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s]" << std::endl;
    return min_values;
}

void KdTree::delete_tree(Node *current_node)
{
    if (current_node == nullptr)
        return;
    delete_tree(current_node->left);
    delete_tree(current_node->right);
    delete current_node;
}

Node* KdTree::searchNN(std::vector<double> Q, Node *Root, int cd, std::shared_ptr<Rect> BB, double best_dist)
{
    /*
    Defines nearest neighbour search algorithm in the KDtree: more info [here](https://en.wikipedia.org/wiki/K-d_tree#Nearest_neighbour_search)
    param:
        inputs:
            Q: Query point of which the nearest neighbor has to be found
            Root: Tree that contains all nodes of which one will be the nearest neighbour to Q
            cd: hyperparamater used to store the alternating dimension checks
            BB: rectangle struct defined in rect.h; is defined as the bounding box of each node. more info [here](https://gopalcdas.com/2017/05/24/construction-of-k-d-tree-and-using-it-for-nearest-neighbour-search/)
        returns:
            Nearest neighbour pointer of Q within kdtree Root

    */
    static Node* best;

    if (best_dist == -1) // a start condition
    {
        // initial best estimate as the parent of inserted query point, Q
        Node *currentNode = insert(Q, Root, 0);
        auto catchv = 0;
        // auxillary variable for early stopping
        best = currentNode;
        // we define the best node to be the root of the tree Root
        while (!currentNode->isLeaf())
        {
            // go through the whole Root tree until you find our inserted Q, i.e. currentNode is a leaf
            if (Q[cd] < currentNode->point[cd])
            {
                best = currentNode;
                if (!(currentNode->left == nullptr))
                    currentNode = currentNode->left; // safety
            }
            else
            {
                best = currentNode;
                if (!(currentNode->right == nullptr))
                    currentNode = currentNode->right;
            } // safety
            cd = (cd + 1) % k;
            // our initial best estimate is the direct parent of the leaf node Q
        }
        best_dist = distance(Q, best->point);  // rewrite the best_dist

        std::cout << "init best distance: " << best_dist << std::endl;
        print_vector(best->point);
    }

    /*
    Now we check neighboring nodes for better estimates, :)
    Recursively go through all parents of our initial best estimate, with the bounding box of each and look for better estimates
    We use auxillary distance functions form the utils.cpp files, including distances between rect and vector
    */
    if (distance(Q, BB) > best_dist)
    {
        return nullptr;
    }
    double dist = distance(Q, Root->point);
    if (dist < best_dist)
    {
        best = Root;
        best_dist = dist;
    }
    if (Q[cd] < Root->point[cd])
    {
        searchNN(Q, Root->left, (cd + 1) % 2, BB->trimLeft(cd, Root->point), best_dist);
        searchNN(Q, Root->right, (cd + 1) % 2, BB->trimRight(cd, Root->point), best_dist);
    }
    else
    {
        searchNN(Q, Root->right, (cd + 1) % 2, BB->trimRight(cd, Root->point), best_dist);
        searchNN(Q, Root->left, (cd + 1) % 2, BB->trimLeft(cd, Root->point), best_dist);
    }

    std::cout << "final best distance: "<< dist << std::endl;

    return best;
}