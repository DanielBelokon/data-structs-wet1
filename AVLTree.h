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

private:
    Node<T> *addRecursive(T data, Node<T> *current, Node<T> *parent);
    void replaceChild(Node<T> *parent, Node<T> *child, Node<T> *newChild);

    void RR(Node<T> *current, Node<T> *parent);
    void LL(Node<T> *current, Node<T> *parent);
    void LR(Node<T> *current, Node<T> *parent);
    void RL(Node<T> *current, Node<T> *parent);
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
    addRecursive(data, current, nullptr);
}

template <typename T>
Node<T> *AVLTree<T>::addRecursive(T data, Node<T> *current, Node<T> *parent)
{
    if (current == nullptr)
    {
        current = new Node<T>(data);
        size++;
        return current;
    }
    if (compare(data, current->getData()))
    {
        Node<T> *newNode = addRecursive(data, current->getLeft(), current);
        if (newNode != nullptr)
            current->setLeft(newNode);
    }
    else
    {
        Node<T> *newNode = addRecursive(data, current->getRight(), current);
        if (newNode != nullptr)
            current->setRight(newNode);
    }
    current->updateHeight();

    int balanceFactor = current->getBalanceFactor();
    if (balanceFactor > 1)
    {
        if (current->getLeft()->getBalanceFactor() == 1)
        {
            LL(current, parent);
        }
        else
        {
            LR(current, parent);
        }
    }
    else if (balanceFactor < -1)
    {
        if (current->getRight()->getBalanceFactor() == -1)
        {
            RR(current, parent);
        }
        else
        {
            RL(current, parent);
        }
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::RR(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_root = root->getRight();
    replaceChild(parent, root, new_root);
    root->setRight(new_root->getLeft());
    new_root->setLeft(root);

    new_root->getLeft()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::RL(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_right = root->getRight();
    Node<T> *new_root = new_right->getLeft();
    replaceChild(parent, root, new_root);
    new_root->setRight(new_right);
    new_right->setLeft(nullptr);

    new_root->setLeft(root);
    root->setRight(nullptr);

    new_root->getLeft()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::LL(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_root = root->getLeft();
    replaceChild(parent, root, new_root);
    root->setLeft(new_root->getRight());
    new_root->setRight(root);

    new_root->getRight()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::LR(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_left = root->getLeft();
    Node<T> *new_root = new_left->getRight();
    replaceChild(parent, root, new_root);
    new_root->setLeft(new_left);
    new_left->setLeft(nullptr);

    new_root->setRight(root);
    root->setLeft(nullptr);

    new_root->getRight()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::replaceChild(Node<T> *parent, Node<T> *child, Node<T> *newChild)
{
    if (parent == nullptr)
    {
        root = newChild;
        return;
    }

    if (parent->getLeft() == child)
    {
        parent->setLeft(newChild);
    }
    else
    {
        parent->setRight(newChild);
    }
}

#endif // AVL_TREE_H