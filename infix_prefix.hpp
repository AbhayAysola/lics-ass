/**
 * @file infix_prefix.hpp
 * @brief Task 1 — conversion from infix to prefix notation.
 */

#ifndef INFIX_PREFIX_HPP
#define INFIX_PREFIX_HPP

#include <string>

/**
 * @brief Tests whether @p c is a propositional connective used in this assignment.
 * @param c Character from a formula (`~`, `+`, `*`, `>`).
 * @return true if @p c is a connective.
 */
bool is_connective(char c);

/**
 * @brief Converts a fully parenthesized infix formula to prefix form.
 *
 * Operands are single lowercase letters. The input must be well-formed and
 * fully parenthesized (e.g. `(p>q)`, `(~p)`).
 *
 * @param infix Infix formula string.
 * @return Equivalent prefix expression (no spaces).
 *
 * @par Complexity
 * Time O(n), space O(n) for @p n = infix.size().
 */
std::string infix_to_prefix(const std::string &infix);

#endif
