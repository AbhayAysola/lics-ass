/**
 * @file tree.hpp
 * @brief Binary parse tree for propositional formulas (Tasks 2–4).
 */

#ifndef TREE_HPP
#define TREE_HPP

#include <map>
#include <string>

/**
 * @brief Rooted binary parse tree for a propositional formula.
 *
 * Internal nodes store a connective in @c name (`~`, `+`, `*`, `>`).
 * Leaves store an atom name; truth value is held in @c atom_value.
 * For negation, only @c r is used; @c l is null.
 */
class Tree
{
public:
    Tree *l;              /**< Left child (binary operators). */
    Tree *r;              /**< Right child, or sole child for `~`. */
    std::string name;     /**< Connective symbol or atom name. */
    bool atom_value;      /**< Truth value when @c name is an atom. */

    /**
     * @brief Constructs a node.
     * @param left Left subtree (null for atoms and `~`).
     * @param right Right subtree.
     * @param sym Connective or atom label.
     * @param is_atom If true, this node is a propositional atom.
     */
    Tree(Tree *left, Tree *right, const std::string &sym, bool is_atom = false);

    /** @return true if @c name is a connective operator. */
    bool is_operator() const;

    /**
     * @brief Evaluates the formula bottom-up using current atom values.
     * @return Truth value of the subtree.
     */
    bool evaluate() const;

    /**
     * @brief Sets truth value for atom nodes only.
     * @param v Truth value to store.
     */
    void set_atom_value(bool v);

    /**
     * @brief Builds a parse tree from a prefix expression (Task 2).
     * @param prefix Prefix formula (output of infix_to_prefix()).
     * @return Root of a new tree, or nullptr on empty input.
     */
    static Tree *from_prefix(const std::string &prefix);

    /**
     * @brief Post-order delete of @p root and all descendants.
     * @param root Tree to free (may be nullptr).
     */
    static void destroy(Tree *root);

    /**
     * @brief Tree height (Task 4, recursive). Atoms have height 0.
     * @return Height of the subtree.
     */
    int height_recursive() const;

    /**
     * @brief Tree height (Task 4, iterative, explicit stack).
     * @return Height of the subtree.
     */
    int height_iterative() const;

    /**
     * @brief In-order style infix with parentheses (Task 3, recursive).
     * @return Fully parenthesized infix string.
     */
    std::string infix_recursive() const;

    /**
     * @brief Infix reconstruction (Task 3, iterative).
     * @return Fully parenthesized infix string.
     */
    std::string infix_iterative() const;

    /**
     * @brief Pre-order traversal string (Task 3, recursive).
     * @return Prefix-style character sequence (no spaces).
     */
    std::string preorder_recursive() const;

    /**
     * @brief Pre-order traversal string (Task 3, iterative).
     * @return Prefix-style character sequence (no spaces).
     */
    std::string preorder_iterative() const;

    /**
     * @brief Post-order traversal string (Task 3, recursive).
     * @return Post-order character sequence (no spaces).
     */
    std::string postorder_recursive() const;

    /**
     * @brief Post-order traversal string (Task 3, iterative).
     * @return Post-order character sequence (no spaces).
     */
    std::string postorder_iterative() const;

    /**
     * @brief Collects distinct atom names in the tree.
     * @param atoms Map atom → current truth value (inserted if missing).
     */
    void collect_atoms(std::map<std::string, bool> &atoms) const;
};

#endif
