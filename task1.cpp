/**
 * @file task1.cpp
 * @brief CLI driver for Task 1 (infix → prefix only).
 */

#include <fstream>
#include <iostream>
#include <string>

#include "infix_prefix.hpp"

namespace
{

constexpr const char *kInputHint =
    "Input must be a well-formed, fully parenthesized formula "
    "(connectives: ~ + * >).\n";

void print_conversion(const std::string &infix)
{
    std::cout << "Infix  : " << infix << '\n';
    std::cout << "Prefix : " << infix_to_prefix(infix) << '\n';
}

bool run_batch_file(const char *path)
{
    std::ifstream file(path);
    if (!file)
        return false;

    std::string line;
    bool any = false;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        print_conversion(line);
        std::cout << '\n';
        any = true;
    }
    return any;
}

} // namespace

/**
 * @brief Entry point for `task1` binary.
 *
 * Usage:
 * - `task1` — read one formula from stdin.
 * - `task1 path.txt` — one formula per line.
 * - `task1 "(p>q)"` — single formula argument if path is not a file.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 on read failure.
 */
int main(int argc, char *argv[])
{
    std::cout << kInputHint;

    if (argc == 2)
    {
        if (run_batch_file(argv[1]))
            return 0;

        print_conversion(argv[1]);
        return 0;
    }

    std::string infix;
    if (!(std::cin >> infix))
        return 1;

    print_conversion(infix);
    return 0;
}
