#ifndef __UTILS_H_
#define __UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "node.h"

extern const int k;

std::ostream &operator<<(std::ostream &os, std::vector<double> vec);

std::vector<std::vector<double>> generate_numbers(int n);

void print_vector(const std::vector<double>& Vector);

void write_to_csv (const std::vector<std::vector<double>>& generated_numbers,
                   const std::string& filename = "../data/generated_values.csv");

std::vector<std::vector<double>> read_from_csv (const std::string& filename);

void test_tree_construction();

void test_find_min();

#endif
