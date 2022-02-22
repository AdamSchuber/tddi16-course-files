/*
 * AVL_Tree.h    (c) Tommy Olsson, IDA, 2007-05-02
 * uppdated to C++11 September 2015
 *
 * When problems occur, the exception AVL_Tree_error is thrown.
 *
 * operator<< is assumed to be defined for Comparable.
 */
#ifndef AVLTREE_INC
#define AVLTREE_INC 1
#include <iosfwd>
#include <stdexcept>

class AVL_Tree_error : public std::logic_error {
public:
    explicit AVL_Tree_error(const std::string& what_arg)
        : std::logic_error(what_arg) {}
};

template <typename Comparable> class AVL_Tree_Node;

template <typename Comparable>
class AVL_Tree {
public:
    AVL_Tree();
    AVL_Tree(const AVL_Tree &o);
    AVL_Tree(AVL_Tree &&o);
    ~AVL_Tree();
    AVL_Tree &operator=(const AVL_Tree &rhs);
    AVL_Tree &operator=(AVL_Tree &&rhs);

    void insert(const Comparable &element);
    void remove(const Comparable &element);
    bool member(const Comparable &element) const;

    Comparable &find(const Comparable &element) const;
    Comparable &find_min() const;
    Comparable &find_max() const;

    void clear();
    bool empty() const;

    void print(std::ostream&) const;
    void print_tree(std::ostream&) const;

    void swap(AVL_Tree &other);

private:
    using Node = AVL_Tree_Node<Comparable>;
    using Node_Pointer = AVL_Tree_Node<Comparable>*;

    Node_Pointer root;
};

template <typename Comparable>
void swap(AVL_Tree<Comparable>&, AVL_Tree<Comparable>&);

template <typename Comparable>
std::ostream &operator<<(std::ostream&, const AVL_Tree<Comparable>&);

#include "avl_tree.cpp"

#endif
