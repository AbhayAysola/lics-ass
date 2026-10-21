#ifndef TREE_HPP
#define TREE_HPP

#include <map>
#include <string>

class Tree
{
public:
    Tree *l;
    Tree *r;
    std::string name;
    bool atom_value;

    Tree(Tree *left, Tree *right, const std::string &sym, bool is_atom = false);

    bool is_operator() const;
    bool evaluate() const;
    void set_atom_value(bool v);

    static Tree *from_prefix(const std::string &prefix);
    static void destroy(Tree *root);

    int height_recursive() const;
    int height_iterative() const;

    std::string infix_recursive() const;
    std::string infix_iterative() const;
    std::string preorder_recursive() const;
    std::string preorder_iterative() const;
    std::string postorder_recursive() const;
    std::string postorder_iterative() const;

    void collect_atoms(std::map<std::string, bool> &atoms) const;
};

#endif
