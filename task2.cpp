#include <fstream>
#include <iostream>
#include <string>

#include "infix_prefix.hpp"
#include "tree.hpp"

int main(int argc, char *argv[])
{
    std::string infix;
    std::cout << "NOTE : infix needs to be well formed and fully parenthesized\n";

    if (argc == 2)
    {
        std::ifstream file(argv[1]);
        if (file.is_open())
        {
            while (std::getline(file, infix))
            {
                if (infix.empty())
                    continue;
                const std::string prefix = infix_to_prefix(infix);
                Tree *root = Tree::from_prefix(prefix);
                std::cout << "Infix  : " << infix << "\n";
                std::cout << "Prefix : " << prefix << "\n";
                std::cout << "Root op: " << (root ? root->name : "?") << "\n\n";
                Tree::destroy(root);
            }
            return 0;
        }
        infix = argv[1];
    }
    else
    {
        std::cin >> infix;
    }

    const std::string prefix = infix_to_prefix(infix);
    Tree *root = Tree::from_prefix(prefix);
    std::cout << "Infix  : " << infix << "\n";
    std::cout << "Prefix : " << prefix << "\n";
    std::cout << "Infix from tree: " << (root ? root->infix_recursive() : "") << "\n";
    Tree::destroy(root);
    return 0;
}
