#include<iostream>
#include<vector>
#define K 2

int main()
{
    std::vector<double> v1;
    // v1.push_back(0.);
    v1.push_back(1.);
    // v1.push_back(1.);

    for (std::vector<double>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		std::cout << (*it) << " ";
	}
    
    return 0;

}


// void delete_node(std::vector<std::vector<double>> tree, std::vector<double> &node_to_delete)
// {
//     // // find the node in the tree, and delete it
//     // (search(&node_to_delete, &tree))? std::cout << "Found\n": std::cout << "Not Found\n";

//     tree.erase(std::remove(tree.begin(), tree.end(), node_to_delete), tree.end());
//     std::cout << "Successfully deleted node: " << node_to_delete << std::endl;

//     // // reconstuct the tree again
//     // // TODO: find a more efficient way to do this
//     // for (auto &elem : value_vectors)
//     // {
//     //     root = insert(elem, root);
//     // }
// }

