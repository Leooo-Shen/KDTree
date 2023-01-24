#include "../include/my_kd_tree.h"

// test dimension = 2
extern const int k{2};

void test_tree_construction()
{
    /*Generate a tree based on preconceived data and print it (for testing);
        The tree struture should be the same as in the test_tree.jpg.

    Note: due to the tree-construction strategy that follows the order of the point,
          change the order of vectors may change the tree structure.
          This is fine if we actually want to use the tree for searching.
          Different construction strategies: (1) starting from the median of the current dimension, which will generate the so called "balanced tree"
                                             (2) use the largest variance in current dimension
    */

    KdTree kdtree;

    // pre-defined value vectors for testing
    auto value_vectors = std::vector<std::vector<double>>{{7, 2}, {5, 4}, {9, 6}, {2, 3}, {4, 7}, {8, 1}};

    auto tree_root = kdtree.construct(value_vectors);

    kdtree.print_tree("", tree_root);

    kdtree.delete_tree(tree_root);
}

void test_find_min()
{
    /*Generate a tree based on preconceived data and find the minimum value of all dimension (for testing);
        Ground Truth: min of dim0: -5.1;  min of dim1: -7.00

    Note: due to the tree-construction strategy that follows the order of the point,
          change the order of vectors may change the tree structure.
          This is fine if we actually want to use the tree for searching.
          Different construction strategies: (1) starting from the median of the current dimension, which will generate the so called "balanced tree"
                                             (2) use the largest variance in current dimension
    */

    KdTree kdtree;

    // pre-defined value vectors for testing
    auto value_vectors = std::vector<std::vector<double>>{{-5.1, 2.09}, {5.21, 4.3}, {9.6, 6}, {2.23, 3.01}, {4.34, -7.03}, {8.32, 1.67}};

    auto tree_root = kdtree.construct(value_vectors);

    // auto min0 = kdtree.find_min(tree_root, 0);
    // std::cout << min0 << std::endl;
    kdtree.find_min_all(tree_root);

    kdtree.delete_tree(tree_root);
}


void test_find_NN()
{
    /*Generate a tree based on preconceived data and find the nearest vector of Target vector (for testing);
        Targte: (-5,2)
        Ground Truth NN: (-5,1, 2,09) 

    Note: due to the tree-construction strategy that follows the order of the point,
          change the order of vectors may change the tree structure.
          This is fine if we actually want to use the tree for searching.
          Different construction strategies: (1) starting from the median of the current dimension, which will generate the so called "balanced tree"
                                             (2) use the largest variance in current dimension
    */

    KdTree kdtree;
    std::shared_ptr<Rect> init_rect(new Rect(-200, -200, 200, 200));
    std::vector<double> Target = {-5, 2};


    // pre-defined value vectors for testing
    auto value_vectors = std::vector<std::vector<double>>{{-5.1, 2.09}, {5.21, 4.3}, {9.6, 6}, {2.23, 3.01}, {4.34, -7.03}, {8.32, 1.67}};

    
    // std::string filepath = "../data/generated_values_middle.csv";
    // auto value_vectors = read_from_csv(filepath);

    auto tree_root = kdtree.construct(value_vectors);
    kdtree.print_tree("", tree_root);

    auto NN = kdtree.searchNN(Target, tree_root, 0, init_rect);

    std::cout << "Nearest Neighbor: " ;
    print_vector(NN->point);

    kdtree.delete_tree(tree_root);
}




int main()
{
    std::cout << "####### Test tree construction #######" << std::endl;
    test_tree_construction();

    std::cout << std::endl
              << "####### Test find min #######" << std::endl;
    test_find_min();

    // std::cout << std::endl
    //           << "####### Test find nearest neighbor #######" << std::endl;
    // test_find_NN();

    return 0;
}