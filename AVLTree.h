#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "TreeNode.h"

template <typename T>
class AVLTree
{
private:
    Node<T> *root;
    int size;

    bool (*customCompare)(const T &a, const T &b);

public:
    class iterator
    {
    public:
        Node<T> *current;
        AVLTree *tree;
    };

    AVLTree(bool (*customCompare)(const T &a, const T &b) = nullptr) : root(nullptr), size(0), customCompare(customCompare)
    {
    }

    void add(T data);

    void remove(T data);
    void merge(AVLTree<T> *tree);

    int getSize();

    T search(int key);
    T *getInOrderArray(int amount = 0);

    T *filter();

    ~AVLTree() = default;
    bool compare(Node<T> const &node1, Node<T> const &node2)
    {
        if (customCompare != nullptr)
        {
            return customCompare(node1.getData(), node2.getData());
        }
        return node1.getData() < node2.getData();
    }

    bool compare(Node<T> &node1, Node<T> &node2)
    {
        return compare(node1, node2);
    }

private:
    bool addRecursive(Node<T> *newNode, Node<T> *current);

    void RR(Node<T> *&root);
    void LL(Node<T> *&root);
    void LR(Node<T> *&root);
    void RL(Node<T> *&root);
};

template <typename T>
void AVLTree<T>::add(T data)
{
    if (root == nullptr)
    {
        root = new Node<T>(data);
        size++;
        return;
    }
    Node<T> *current = root;
    Node<T> *newNode = new Node<T>(data);
    addRecursive(newNode, current);
}

template <typename T>
bool AVLTree<T>::addRecursive(Node<T> *newNode, Node<T> *current)
{
    if (current == nullptr)
    {
        size++;
        return true;
    }

    if (compare(newNode->getData(), current->getData()))
    {

        if (addRecursive(newNode, current->getLeft()))
        {
            current->setLeft(*newNode);
        }
    }
    else
    {
        if (addRecursive(newNode, current->getRight()))
        {
            current->setRight(*newNode);
        }
    }
    return false;
}

template <typename T>
void RR(Node<T> *&root)
{
    Node<T> *new_root = root->getRight();
    root->setRight(new_root->getLeft());
    new_root->setLeft(root);
    root = new_root;
}

template <typename T>
void RL(Node<T> *&root)
{
    Node<T> *new_right = root->getRight();
    Node<T> *new_root = new_right->getLeft();
    // Swap the right child of the root with the left child of the right child
    root->setRight(new_root->getLeft());
    new_right->setLeft(new_root->getRight());
    // Rotate right
    new_root->setLeft(root);
    new_root->setRight(new_right);
    root = new_root;
}

template <typename T>
void LL(Node<T> *&root)
{
    Node<T> *new_root = root->getLeft();
    root->setLeft(new_root->getRight());
    new_root->setRight(root);
    root = new_root;
}

template <typename T>
void LR(Node<T> *&root)
{
    Node<T> *new_left = root->getLeft();
    Node<T> *new_root = new_left->getRight();
    root->setLeft(new_root->getRight());
    new_left->setRight(new_root->getLeft());
    new_root->setRight(root);
    new_root->setLeft(new_left);
    root = new_root;
}

#endif // AVL_TREE_H