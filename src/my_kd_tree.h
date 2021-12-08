#ifndef __HELPER_H_
#define __HELPER_H_
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
extern const int k;
struct Node;

std::ostream &operator<<(std::ostream &os, std::vector<double> vec);

std::vector<std::vector<double>> generate_numbers(int n);

void print_array(std::vector<std::vector<double>> generate_numbers);

Node *insert(std::vector<double> &x, Node *parent, unsigned cd = 0);

bool arePointsSame(std::vector<double> point1, std::vector<double> point2);

bool search(Node *root, std::vector<double> search_point, unsigned depth = 0);

void print_kd_tree(Node *tree, unsigned depth=0);

void write_to_csv (std::vector<std::vector<double>>& generated_numbers,
                   std::string filename = "../data/generated_values.csv");

std::vector<std::vector<double>> read_from_csv (std::string filename);

Node * delete_node(std::vector<std::vector<double>> &origin_vecs, std::vector<double> point_to_delete);

#endif
