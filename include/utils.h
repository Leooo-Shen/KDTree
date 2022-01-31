#ifndef __UTILS_H_
#define __UTILS_H_

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "rect.h"


std::ostream &operator<<(std::ostream &os, std::vector<double> vec);

std::vector<std::vector<double>> generate_numbers(int n);

void print_vector(const std::vector<double>& Vector);

void write_to_csv (const std::vector<std::vector<double>>& generated_numbers,
                   const std::string& filename = "../data/generated_values.csv");

std::vector<std::vector<double>> read_from_csv (const std::string& filename);

void test_tree_construction();

void test_find_min();


double distance(std::vector<double> A, std::vector<double> B);

double max(double a, double b, double c);

double distance(std::vector<double> Q,Rect* BB);

#endif
