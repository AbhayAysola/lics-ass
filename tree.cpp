#include "tree.hpp"

#include <algorithm>
#include <cctype>
#include <stack>
#include <vector>

namespace
{

bool is_connective_char(char c)
{
    return c == '~' || c == '*' || c == '+' || c == '>';
}

bool is_connective_str(const std::string &s)
{
    return s.size() == 1 && is_connective_char(s[0]);
}

Tree *build_from_prefix(const std::string &prefix, size_t &pos)
{
    if (pos >= prefix.size())
        return nullptr;

    const char c = prefix[pos++];
    const std::string sym(1, c);

    if (!is_connective_char(c))
        return new Tree(nullptr, nullptr, sym, true);

    if (c == '~')
    {
        Tree *child = build_from_prefix(prefix, pos);
        return new Tree(nullptr, child, sym);
    }

    Tree *left = build_from_prefix(prefix, pos);
    Tree *right = build_from_prefix(prefix, pos);
    return new Tree(left, right, sym);
}

} // namespace

Tree::Tree(Tree *left, Tree *right, const std::string &sym, bool /*is_atom*/)
    : l(left), r(right), name(sym), atom_value(true)
{
}

bool Tree::is_operator() const
{
    return is_connective_str(name);
}

bool Tree::evaluate() const
{
    if (name == "~")
        return !r->evaluate();
    if (name == "+")
        return l->evaluate() || r->evaluate();
    if (name == "*")
        return l->evaluate() && r->evaluate();
    if (name == ">")
        return !l->evaluate() || r->evaluate();
    return atom_value;
}

void Tree::set_atom_value(bool v)
{
    if (!is_operator())
        atom_value = v;
}

Tree *Tree::from_prefix(const std::string &prefix)
{
    size_t pos = 0;
    return build_from_prefix(prefix, pos);
}

void Tree::destroy(Tree *root)
{
    if (!root)
        return;
    destroy(root->l);
    destroy(root->r);
    delete root;
}

int Tree::height_recursive() const
{
    if (!is_operator())
        return 0;
    if (name == "~")
        return 1 + r->height_recursive();
    return 1 + std::max(l->height_recursive(), r->height_recursive());
}

int Tree::height_iterative() const
{
    int max_h = 0;
    std::stack<std::pair<const Tree *, int>> st;
    st.push({this, 0});

    while (!st.empty())
    {
        auto [node, depth] = st.top();
        st.pop();
        max_h = std::max(max_h, depth);

        if (!node->is_operator())
            continue;

        if (node->name == "~")
            st.push({node->r, depth + 1});
        else
        {
            st.push({node->r, depth + 1});
            st.push({node->l, depth + 1});
        }
    }
    return max_h;
}

std::string Tree::infix_recursive() const
{
    if (!is_operator())
        return name;

    if (name == "~")
        return "(~" + r->infix_recursive() + ")";

    return "(" + l->infix_recursive() + name + r->infix_recursive() + ")";
}

std::string Tree::infix_iterative() const
{
    std::string out;
    struct Frame
    {
        const Tree *n;
        int phase;
    };
    std::stack<Frame> st;
    st.push({this, 0});

    while (!st.empty())
    {
        Frame f = st.top();
        st.pop();
        const Tree *node = f.n;

        if (!node->is_operator())
        {
            out += node->name;
            continue;
        }

        if (node->name == "~")
        {
            if (f.phase == 0)
            {
                out += "(~";
                st.push({node, 1});
                st.push({node->r, 0});
            }
            else
                out += ")";
            continue;
        }

        if (f.phase == 0)
        {
            out += "(";
            st.push({node, 1});
            st.push({node->l, 0});
        }
        else if (f.phase == 1)
        {
            out += node->name;
            st.push({node, 2});
            st.push({node->r, 0});
        }
        else
            out += ")";
    }
    return out;
}

std::string Tree::preorder_recursive() const
{
    if (!is_operator())
        return name;
    if (name == "~")
        return name + r->preorder_recursive();
    return name + l->preorder_recursive() + r->preorder_recursive();
}

std::string Tree::preorder_iterative() const
{
    std::string out;
    std::stack<const Tree *> st;
    st.push(this);

    while (!st.empty())
    {
        const Tree *node = st.top();
        st.pop();
        out += node->name;

        if (!node->is_operator())
            continue;

        if (node->name == "~")
            st.push(node->r);
        else
        {
            st.push(node->r);
            st.push(node->l);
        }
    }
    return out;
}

std::string Tree::postorder_recursive() const
{
    if (!is_operator())
        return name;
    if (name == "~")
        return r->postorder_recursive() + name;
    return l->postorder_recursive() + r->postorder_recursive() + name;
}

std::string Tree::postorder_iterative() const
{
    std::string out;
    std::stack<const Tree *> st;
    std::stack<const Tree *> out_st;
    st.push(this);

    while (!st.empty())
    {
        const Tree *node = st.top();
        st.pop();
        out_st.push(node);

        if (!node->is_operator())
            continue;

        if (node->name == "~")
            st.push(node->r);
        else
        {
            st.push(node->r);
            st.push(node->l);
        }
    }

    while (!out_st.empty())
    {
        out += out_st.top()->name;
        out_st.pop();
    }
    return out;
}

void Tree::collect_atoms(std::map<std::string, bool> &atoms) const
{
    if (!is_operator())
    {
        atoms[name] = atom_value;
        return;
    }
    if (name == "~")
    {
        r->collect_atoms(atoms);
        return;
    }
    l->collect_atoms(atoms);
    r->collect_atoms(atoms);
}
