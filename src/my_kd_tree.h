#ifndef __HELPER_H_
#define __HELPER_H_
#include <iostream>
#include <string>
#include <vector>

extern const int k;
struct Node;

std::ostream &operator<<(std::ostream &os, std::vector<double> vec);

// std::ostream& operator<<(std::ostream& os, Node node);

std::vector<std::vector<double>> generate_numbers(int n);

void print_array(std::vector<std::vector<double>> generate_numbers);

Node *insert(std::vector<double> &x, Node *parent, unsigned int cd = 0);

bool arePointsSame(std::vector<double> point1, std::vector<double> point2);

bool search(Node *root, std::vector<double> point, unsigned depth = 0);

Node *minNode(Node *x, Node *y, Node *z, int comparing_d);

Node *findMin(Node *root, unsigned int comparing_d, unsigned int depth=0);

Node *deleteNode(Node *root, std::vector<double> point, int depth=0);

#endif
