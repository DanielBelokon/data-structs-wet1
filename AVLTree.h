#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "Exceptions.h"
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

    void print(std::ostream &out);

    int getSize();
    Node<T> *getRoot() { return root; }

    T search(T object);
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
    void printRecursive(Node<T> *current, std::ostream &out);
    void replaceChild(Node<T> *parent, Node<T> *child, Node<T> *newChild);

    void balance(Node<T> *current, Node<T> *parent);
    Node<T> *findNode(T object);
    void InOrderAux(T *array, int *index, Node<T> *current, int amount);

    void RR(Node<T> *current, Node<T> *parent);
    void LL(Node<T> *current, Node<T> *parent);
    void LR(Node<T> *current, Node<T> *parent);
    void RL(Node<T> *current, Node<T> *parent);
};

template <typename T>
int AVLTree<T>::getSize()
{
    return size;
}

template <typename T>
void AVLTree<T>::print(std::ostream &out)
{
    if (root == nullptr)
    {
        out << "Tree is empty" << std::endl;
        return;
    }
    printRecursive(root, out);
}

template <typename T>
void AVLTree<T>::printRecursive(Node<T> *current, std::ostream &out)
{
    if (current == nullptr)
    {
        return;
    }
    printRecursive(current->getLeft(), out);
    out << current->getData() << " ";
    printRecursive(current->getRight(), out);
}

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
    balance(current, parent);

    return nullptr;
}

template <typename T>
void AVLTree<T>::balance(Node<T> *current, Node<T> *parent)
{
    if (current == nullptr)
    {
        return;
    }

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
    LL(root->getRight(), root);
    RR(root, parent);
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
    RR(root->getLeft(), root);
    LL(root, parent);
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

template <typename T>
T AVLTree<T>::search(T object)
{
    Node<T> *result = findNode(object);
    if (result == nullptr)
    {
        return nullptr;
    }
    else
        return result->getData();
}

template <typename T>
Node<T> *AVLTree<T>::findNode(T object)
{
    Node<T> *current = root;
    while (current != nullptr)
    {
        if (compare(current->getData(), object))
        {
            current = current->getRight();
        }
        else if (compare(object, current->getData()))
        {
            current = current->getLeft();
        }
        else
        {
            return current;
        }
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::remove(T object)
{
    Node<T> *current = root;
    Node<T> *prev = nullptr;
    while (current != nullptr)
    {
        if (compare(current->getData(), object))
        {
            prev = current;
            current = current->getRight();
        }
        else if (compare(object, current->getData()))
        {
            prev = current;
            current = current->getLeft();
        }
        else
        {
            if (current->getRight() == nullptr && current->getLeft() == nullptr)
            {
                replaceChild(prev, current, nullptr);
                delete current;
                current = nullptr;
            }
            else if (current->getRight() == nullptr && current->getLeft() != nullptr)
            {
                Node<T> *temp = current->getLeft();
                replaceChild(prev, current, temp);
                delete current;
                current = nullptr;
            }
            else if (current->getRight() != nullptr && current->getLeft() == nullptr)
            {
                Node<T> *temp = current->getRight();
                replaceChild(prev, current, temp);
                delete current;
                current = nullptr;
            }
            else
            {
                Node<T> *temp = current->getRight();
                while (temp->getLeft() != nullptr)
                {
                    temp = temp->getLeft();
                }
                current->setData(temp->getData());
                remove(temp->getData());
            }
        }
    }
    size--;
}

template <typename T>
T *AVLTree<T>::getInOrderArray(int amount)
{
    if (amount == 0 || size < amount)
    {
        amount = size;
    }

    T *array = new T[amount];
    int index = 0;
    InOrderAux(array, &index, root, amount);
    return array;
}

template <typename T>
void AVLTree<T>::InOrderAux(T *array, int *index, Node<T> *current, int amount)
{
    if (current == nullptr || *index >= amount)
    {
        return;
    }

    InOrderAux(array, index, current->getLeft(), amount);
    array[*index] = current->getData();
    (*index)++;
    InOrderAux(array, index, current->getRight(), amount);
}

#endif // AVL_TREE_H