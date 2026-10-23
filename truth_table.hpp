/**
 * @file truth_table.hpp
 * @brief Task 5 — truth assignment and full truth table printing.
 */

#ifndef TRUTH_TABLE_HPP
#define TRUTH_TABLE_HPP

#include "tree.hpp"

#include <iostream>
#include <vector>

/**
 * @brief Evaluates the tree for one row of a truth table.
 *
 * Atoms are assigned in order: row bit pattern maps to @p atoms[0], @p atoms[1], …
 *
 * @param root Parse tree (atom fields are updated in place).
 * @param atoms Sorted list of atom names.
 * @param row Row index from `0` to `2^atoms.size() - 1`.
 * @return Formula truth value for that row.
 */
bool evaluate_with_row(Tree *root, const std::vector<std::string> &atoms, unsigned row);

/**
 * @brief Prints a truth table for all atoms in @p root to @p out.
 * @param root Parse tree.
 * @param out Output stream (default `std::cout`).
 */
void print_truth_table(Tree *root, std::ostream &out = std::cout);

#endif
