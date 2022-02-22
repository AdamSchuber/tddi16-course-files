/*
 * AVL_Tree.tcc    (c) Tommy Olsson, IDA, 2007-05-02
 * updated to C++11 September 2015
 */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "avl_tree.h"

using namespace std;

/*
 * AVL_Tree_Node.
 */
template <typename Comparable>
class AVL_Tree_Node
{
private:
    friend class AVL_Tree<Comparable>;

    AVL_Tree_Node(const Comparable &element)
        : element{element}, left{}, right{}, height{} {}

    AVL_Tree_Node(const Comparable &element, AVL_Tree_Node *left, AVL_Tree_Node *right)
        : element{element}, left{left}, right{right}, height{} {}

    Comparable element;
    AVL_Tree_Node *left;
    AVL_Tree_Node *right;
    int height;

    // Aliases to simplify the code
    using Node = AVL_Tree_Node<Comparable>;
    using Node_Pointer = AVL_Tree_Node<Comparable> *;

    // The following functions are called from corresponding functions in AVL_Tree
    static void insert(const Comparable &, Node_Pointer &);
    static void remove(const Comparable &, Node_Pointer &);

    static void clear(Node_Pointer &);

    static Node_Pointer find(const Comparable &, const Node_Pointer);
    static Node_Pointer find_min(const Node_Pointer);
    static Node_Pointer find_max(const Node_Pointer);

    static void print(std::ostream &, const Node_Pointer);
    static void print_tree(std::ostream &, const Node_Pointer, int depth = 0);

    // This function implements deep copying
    static Node_Pointer clone(const Node_Pointer);

    // The following functions are internal help functions for AVL_Tree_Node
    static void single_rotate_with_left_child(Node_Pointer &);
    static void single_rotate_with_right_child(Node_Pointer &);
    static void double_rotate_with_left_child(Node_Pointer &);
    static void double_rotate_with_right_child(Node_Pointer &);

    static void calculate_height(const Node_Pointer);
    static int node_height(const Node_Pointer);

    static void indent(std::ostream &os, int level);
};

/*=============================================*
 *                                             *
 *                AVL_Tree_Node                *
 *                                             *
 *=============================================*/

/**
 * AVL rotations and corrsponding help functions.
 */

/**
 * Return the height of a node (sub tree).
 */
template <typename Comparable>
int AVL_Tree_Node<Comparable>::node_height(const Node_Pointer p)
{
    return (p != nullptr ? p->height : -1);
}

/**
 * Adjust the height for node p.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::calculate_height(const Node_Pointer p)
{
    p->height = 1 + max(node_height(p->left), node_height(p->right));
    //std::cout << "calculating height..." << std::endl;
}

/**
 * Single rotation left-to-right using node k2 as pivot.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::single_rotate_with_left_child(Node_Pointer &k2)
{
    Node_Pointer k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(node_height(k2->left), node_height(k2->right)) + 1;
    k1->height = max(node_height(k1->left), k2->height) + 1;

    k2 = k1;
}

/**
 * Single rotation right-to-left using node k1 as pivot.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::single_rotate_with_right_child(Node_Pointer &k1)
{
    Node_Pointer k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(node_height(k1->right), node_height(k1->left)) + 1;
    k2->height = max(node_height(k2->right), k1->height) + 1;

    k1 = k2;
}

/**
 * Double rotation left-to-right using node k3 as pivot.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::double_rotate_with_left_child(Node_Pointer &k3)
{
    single_rotate_with_right_child(k3->left);
    single_rotate_with_left_child(k3);
}

/**
 * Double rotation right-to-left using node k3 as pivot.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::double_rotate_with_right_child(Node_Pointer &k3)
{
    single_rotate_with_left_child(k3->right);
    single_rotate_with_right_child(k3);
}

/*
 * Member functions for AVL_Tree_Node
 */

/**
 * Insert x in tree t as a new leaf. Check balance and adjust tree if needed.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::insert(const Comparable &x, Node_Pointer &t)
{
    if (t == nullptr)
    {
        t = new Node(x);
        return;
    }

    if (x < t->element)
    {
        insert(x, t->left);

        if (node_height(t->left) - node_height(t->right) == 2)
            if (x < t->left->element)
                single_rotate_with_left_child(t);
            else
                double_rotate_with_left_child(t);
        else
            calculate_height(t);
    }
    else if (t->element < x)
    {
        insert(x, t->right);

        if (node_height(t->right) - node_height(t->left) == 2)
            if (t->right->element < x)
                single_rotate_with_right_child(t);
            else
                double_rotate_with_right_child(t);
        else
            calculate_height(t);
    }
    else
    {
        throw AVL_Tree_error("insättning: finns redan");
    }
}

template <typename Comparable>
void AVL_Tree_Node<Comparable>::remove(const Comparable &x, Node_Pointer &t)
{
    if (t == nullptr)
    {
        return; // kasta exception sen..
    }

    if (x < t->element)
    {
        remove(x, t->left);
        
        if (max(node_height(t->left), node_height(t->right)) - min(node_height(t->left), node_height(t->right)) >= 2)
        {
            //std::cout << "obalans i vänster.. " << std::endl;
            if (node_height(t->right->right) >= node_height(t->right->left))
                single_rotate_with_right_child(t);
            else
                double_rotate_with_right_child(t);
        }
        else
        {
            calculate_height(t);
        }
    }
    else if (x > t->element)
    {
        remove(x, t->right);

        if (max(node_height(t->left), node_height(t->right)) - min(node_height(t->left), node_height(t->right)) >= 2)
        {
            //std::cout << "obalans i höger.. " << std::endl;
            if (node_height(t->left->left) >= node_height(t->left->right))
                single_rotate_with_left_child(t);
            else
                double_rotate_with_left_child(t);
        }
        else
        {
            calculate_height(t);
        }
    }
    else
    {
        // Sökt värde finns i noden t
        Node_Pointer tmp;
        if (t->left != nullptr && t->right != nullptr)
        {
            // Noden har två barn och ersätts med inorder efterföljare
            tmp = find_min(t->right);
            t->element = tmp->element;
            remove(t->element, t->right);

            if (max(node_height(t->left), node_height(t->right)) - min(node_height(t->left), node_height(t->right)) >= 2)
            {
                std::cout << "obalans i höger.. " << std::endl;
                //single_rotate_with_left_child(t);
                if (node_height(t->left->left) >= node_height(t->left->right))
                    single_rotate_with_left_child(t);
                else
                    double_rotate_with_left_child(t);
            }
            else
            {
                calculate_height(t);
            }
        }
        else
        {
            // Noden har inget eller ett barn
            tmp = t;
            if (t->left == nullptr)
                t = t->right;
            else
                t = t->left;

            delete tmp;
        }
    }
}

/**
 * Print elements in ascending order.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::print(ostream &os, const Node_Pointer t)
{
    if (t != nullptr)
    {
        print(os, t->left);
        os << t->element << " ";
        print(os, t->right);
    }
}

/**
 * Print the tree in amazingly beautiful ASCII art.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::print_tree(ostream &os, const Node_Pointer t, int depth)
{
    if (t != nullptr)
    {
        print_tree(os, t->right, depth + 1);

        if (t->right != nullptr)
        {
            indent(os, depth);
            os << " /" << endl;
        }

        indent(os, depth);
        os << t->element << endl;

        if (t->left != nullptr)
        {
            indent(os, depth);
            os << " \\" << endl;
        }

        print_tree(os, t->left, depth + 1);
    }
}

/**
 * Copy the tree.
 */
template <typename Comparable>
AVL_Tree_Node<Comparable> *AVL_Tree_Node<Comparable>::clone(const Node_Pointer t)
{
    if (t != nullptr)
        return new Node(t->element, clone(t->left), clone(t->right));
    else
        return nullptr;
}

/**
 * Look for x in the tree. If found, return av pointer to the node.
 * Otherwise, return nullptr.
 */
template <typename Comparable>
AVL_Tree_Node<Comparable> *AVL_Tree_Node<Comparable>::find(const Comparable &x, const Node_Pointer t)
{
    if (t == nullptr)
        return nullptr;
    else if (x < t->element)
        return find(x, t->left);
    else if (t->element < x)
        return find(x, t->right);
    else
        return t;
}

/**
 * Look for the smallest value (the leftmost node). Return pointer to that node.
 * In case of empty tree, return nullptr.
 */
template <typename Comparable>
AVL_Tree_Node<Comparable> *AVL_Tree_Node<Comparable>::find_min(const Node_Pointer t)
{
    if (t == nullptr)
        return nullptr;
    else if (t->left == nullptr)
        return t;
    else
        return find_min(t->left);
}

/**
 * Look for the biggest value (the rightmost node). Return pointer to that node.
 * In case of empty tree, return nullptr.
 */
template <typename Comparable>
AVL_Tree_Node<Comparable> *AVL_Tree_Node<Comparable>::find_max(const Node_Pointer t)
{
    Node_Pointer p = t;
    if (p != nullptr)
    {
        while (p->right != nullptr)
            p = p->right;
    }
    return p;
}

/**
 * Remove all nodes in the tree.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::clear(Node_Pointer &t)
{
    if (t != nullptr)
    {
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }
}

/**
 * Make indent matching the current tree depth.
 */
template <typename Comparable>
void AVL_Tree_Node<Comparable>::indent(ostream &os, int level)
{
    for (int i = 0; i < level; ++i)
        os << "       ";
}

/*=============================================*
 *                                             *
 *                  AVL_Tree                   *
 *                                             *
 *=============================================*/

/*
 * Constructors, destructor and assignment for AVL_Tree
 */

/**
 * Default constructor.
 */
template <typename Comparable>
AVL_Tree<Comparable>::AVL_Tree() : root{nullptr} {}

/**
 * Copy constructor.
 */
template <typename Comparable>
AVL_Tree<Comparable>::AVL_Tree(const AVL_Tree &value) : root{Node::clone(value.root)} {}

/**
 * Move constructor.
 */
template <typename Comparable>
AVL_Tree<Comparable>::AVL_Tree(AVL_Tree &&value) : root{value.root}
{
    value.root = nullptr;
}

/**
 * Destructor.
 */
template <typename Comparable>
AVL_Tree<Comparable>::~AVL_Tree()
{
    Node::clear(root);
}

/**
 * Assignment operator.
 */
template <typename Comparable>
AVL_Tree<Comparable> &AVL_Tree<Comparable>::operator=(const AVL_Tree<Comparable> &rhs)
{
    AVL_Tree tmp(rhs);
    swap(tmp);
    return *this;
}

/**
 * Move assignment operator.
 */
template <typename Comparable>
AVL_Tree<Comparable> &AVL_Tree<Comparable>::operator=(AVL_Tree<Comparable> &&rhs)
{
    swap(rhs);
    return *this;
}

/*
 * Public member functions for AVL_Tree
 */

/**
 * Insert x in the tree.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::insert(const Comparable &x)
{
    Node::insert(x, root);
}

/**
 * Remove x from the tree.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::remove(const Comparable &x)
{
    // throw AVL_Tree_error("remove: ska implementeras!");
    Node::remove(x, root);
}

/**
 * Check if tree contains x.
 */
template <typename Comparable>
bool AVL_Tree<Comparable>::member(const Comparable &x) const
{
    return Node::find(x, root) != nullptr;
}

/**
 * Look up value x in tree, return reference to that element.
 */
template <typename Comparable>
Comparable &AVL_Tree<Comparable>::find(const Comparable &x) const
{
    Node_Pointer tmp = Node::find(x, root);

    if (tmp == nullptr)
        throw AVL_Tree_error("sökt värde finns ej i trädet");

    return tmp->element;
}

/**
 * Look up the smallest value in the tree, return reference to it.
 */
template <typename Comparable>
Comparable &AVL_Tree<Comparable>::find_min() const
{
    if (root == nullptr)
        throw AVL_Tree_error("försök att finna minst i tomt träd");

    return Node::find_min(root)->element;
}

/**
 * Look up the largest value in the tree, return reference to it.
 */
template <typename Comparable>
Comparable &AVL_Tree<Comparable>::find_max() const
{
    if (root == nullptr)
        throw AVL_Tree_error("försök att finna störst i tomt träd");

    return Node::find_max(root)->element;
}

/**
 * Check if tree is empty.
 */
template <typename Comparable>
bool AVL_Tree<Comparable>::empty() const
{
    return root == nullptr;
}

/**
 * Empty the tree.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::clear()
{
    Node::clear(root);
}

/**
 * Print all values in the tree in ascending order.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::print(ostream &os) const
{
    Node::print(os, root);
}

/**
 * Print the tree.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::print_tree(ostream &os) const
{
    Node::print_tree(os, root, 0);
}

/**
 * Swap this and other.
 */
template <typename Comparable>
void AVL_Tree<Comparable>::swap(AVL_Tree<Comparable> &other)
{
    std::swap(root, other.root);
}

/**
 * Swap x and y.
 */
template <typename Comparable>
void swap(AVL_Tree<Comparable> &x, AVL_Tree<Comparable> &y)
{
    x.swap(y);
}

/**
 * Out-stream operator for AVL_Tree.
 */
template <typename Comparable>
ostream &operator<<(ostream &os, const AVL_Tree<Comparable> &tree)
{
    tree.print_tree(os);
    return os;
}
