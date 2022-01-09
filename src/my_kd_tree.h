#ifndef __HELPER_H_
#define __HELPER_H_
#include <iostream>
#include <string>
#include <vector>
#include<fstream>

#include "node.h"

extern const int k;

std::ostream &operator<<(std::ostream &os, std::vector<double> vec);

std::vector<std::vector<double>> generate_numbers(int n);

Node *insert(std::vector<double> &x, Node *parent, unsigned cd = 0);

bool search(Node *root, std::vector<double> search_point, unsigned depth = 0);

void print_vector(const std::vector<double>& Vector);

void print_kd_tree(const std::string& prefix, const Node* node, bool isLeft);

void write_to_csv (const std::vector<std::vector<double>>& generated_numbers,
                   const std::string& filename = "../data/generated_values.csv");

std::vector<std::vector<double>> read_from_csv (const std::string& filename);

Node * delete_node(std::vector<std::vector<double>> &origin_vecs, std::vector<double> point_to_delete);

#endif
