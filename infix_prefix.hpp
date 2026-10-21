#ifndef INFIX_PREFIX_HPP
#define INFIX_PREFIX_HPP

#include <string>

/** True for assignment connectives: ~ (NOT), + (OR), * (AND), > (IMPLIES). */
bool is_connective(char c);

/**
 * Convert a well-formed, fully parenthesized infix formula to prefix notation.
 * Operands are single lowercase letters; whitespace is not allowed.
 */
std::string infix_to_prefix(const std::string &infix);

#endif
