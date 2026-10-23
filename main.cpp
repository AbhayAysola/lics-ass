/**
 * @file main.cpp
 * @brief CLI driver for `logic_a1` — Tasks 1–5 on each input formula.
 */

#include <fstream>
#include <iostream>
#include <string>

#include "infix_prefix.hpp"
#include "truth_table.hpp"
#include "tree.hpp"

static void run_pipeline(const std::string &infix)
{
    const std::string prefix = infix_to_prefix(infix);
    std::cout << "Infix  : " << infix << '\n';
    std::cout << "Prefix : " << prefix << '\n';

    Tree *root = Tree::from_prefix(prefix);
    if (!root)
    {
        std::cerr << "Failed to build parse tree.\n";
        return;
    }

    std::cout << "Infix (recursive)  : " << root->infix_recursive() << '\n';
    std::cout << "Infix (iterative)  : " << root->infix_iterative() << '\n';
    std::cout << "Preorder (rec)     : " << root->preorder_recursive() << '\n';
    std::cout << "Preorder (iter)    : " << root->preorder_iterative() << '\n';
    std::cout << "Postorder (rec)    : " << root->postorder_recursive() << '\n';
    std::cout << "Postorder (iter)   : " << root->postorder_iterative() << '\n';
    std::cout << "Height (recursive) : " << root->height_recursive() << '\n';
    std::cout << "Height (iterative) : " << root->height_iterative() << '\n';
    std::cout << "Truth table:\n";
    print_truth_table(root);
    std::cout << '\n';

    Tree::destroy(root);
}

/**
 * @brief Entry point for `logic_a1` binary.
 * @see task1.cpp for argument conventions (file, stdin, or literal formula).
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success.
 */
int main(int argc, char *argv[])
{
    std::cout << "NOTE : infix needs to be well formed and fully parenthesized\n";

    if (argc == 2)
    {
        std::ifstream file(argv[1]);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty())
                    continue;
                run_pipeline(line);
            }
            return 0;
        }
        run_pipeline(argv[1]);
        return 0;
    }

    std::string infix;
    std::cin >> infix;
    run_pipeline(infix);
    return 0;
}
