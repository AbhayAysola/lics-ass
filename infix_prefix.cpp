/**
 * @file infix_prefix.cpp
 * @brief Implementation of infix-to-prefix conversion (reverse scan + stack).
 */

#include "infix_prefix.hpp"

#include <algorithm>
#include <stack>

bool is_connective(char c)
{
    return c == '~' || c == '*' || c == '+' || c == '>';
}

std::string infix_to_prefix(const std::string &infix)
{
    std::stack<char> pending;
    std::string prefix_reversed;

    for (auto it = infix.rbegin(); it != infix.rend(); ++it)
    {
        const char c = *it;

        if (c == ')' || is_connective(c))
            pending.push(c);
        else if (c == '(')
        {
            while (!pending.empty() && pending.top() != ')')
            {
                prefix_reversed += pending.top();
                pending.pop();
            }
            if (!pending.empty())
                pending.pop();
        }
        else
            prefix_reversed += c;
    }

    std::reverse(prefix_reversed.begin(), prefix_reversed.end());
    return prefix_reversed;
}
