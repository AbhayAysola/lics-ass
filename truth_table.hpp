#ifndef TRUTH_TABLE_HPP
#define TRUTH_TABLE_HPP

#include "tree.hpp"

#include <iostream>
#include <map>
#include <vector>

/** Assign atom truth values from a row index (0 .. 2^n-1) and evaluate root (Task 5). */
bool evaluate_with_row(Tree *root, const std::vector<std::string> &atoms, unsigned row);

void print_truth_table(Tree *root, std::ostream &out = std::cout);

#endif
