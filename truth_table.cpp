#include "truth_table.hpp"

#include <iomanip>

namespace
{

void set_atom_values(Tree *node, const std::map<std::string, bool> &values)
{
    if (!node)
        return;
    if (!node->is_operator())
    {
        auto it = values.find(node->name);
        if (it != values.end())
            node->set_atom_value(it->second);
        return;
    }
    if (node->name == "~")
    {
        set_atom_values(node->r, values);
        return;
    }
    set_atom_values(node->l, values);
    set_atom_values(node->r, values);
}

} // namespace

bool evaluate_with_row(Tree *root, const std::vector<std::string> &atoms, unsigned row)
{
    std::map<std::string, bool> values;
    const unsigned n = static_cast<unsigned>(atoms.size());
    for (unsigned i = 0; i < n; ++i)
    {
        const bool bit = (row >> (n - 1 - i)) & 1u;
        values[atoms[i]] = bit;
    }
    set_atom_values(root, values);
    return root->evaluate();
}

void print_truth_table(Tree *root, std::ostream &out)
{
    std::map<std::string, bool> atom_map;
    root->collect_atoms(atom_map);

    std::vector<std::string> atoms;
    for (const auto &kv : atom_map)
        atoms.push_back(kv.first);

    const unsigned rows = 1u << atoms.size();

    for (const auto &a : atoms)
        out << std::setw(4) << a;
    out << " | F\n";
    for (size_t i = 0; i < atoms.size(); ++i)
        out << "----";
    out << "-+---\n";

    for (unsigned r = 0; r < rows; ++r)
    {
        for (unsigned i = 0; i < atoms.size(); ++i)
        {
            const bool bit = (r >> (atoms.size() - 1 - i)) & 1u;
            out << std::setw(4) << (bit ? '1' : '0');
        }
        out << " | " << (evaluate_with_row(root, atoms, r) ? '1' : '0') << '\n';
    }
}
