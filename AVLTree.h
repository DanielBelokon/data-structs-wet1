#include "TreeNode.h"

class Condition
{
public:
    Condition();
    ~Condition();
    virtual bool check(TreeNode *node) = 0;
};

template <class T>
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
    void
    RR(Node<T> *&root);
    void LL(Node<T> *&root);
    void LR(Node<T> *&root);
    void RL(Node<T> *&root);
    ~AVLTree();
};

void RR(Node<T> *&root)
{
    Node<T> *temp = root->getRight();
    root->setRight(temp->getLeft());
    temp->setLeft(root);
    root = temp;
}
void RL(Node<T> *&root)
{
    Node<T> *temp = root->getRight();
    Node<T> *temp2 = temp->getLeft();
    root->setRight(temp2->getLeft());
    temp->setLeft(temp2->getRight());
    temp2->setLeft(root);
    temp2->setRight(temp);
    root = temp2;
}
void LL(Node<T> *&root)
{
    Node<T> *temp = root->getLeft();
    root->setLeft(temp->getRight());
    temp->setRight(root);
    root = temp;
}
void LR(Node<T> *&root)
{
    Node<T> *temp = root->getLeft();
    Node<T> *temp2 = temp->getRight();
    root->setLeft(temp2->getRight());
    temp->setRight(temp2->getLeft());
    temp2->setRight(root);
    temp2->setLeft(temp);
    root = temp2;
}

AVLTree::AVLTree(/* args */)
{
}

AVLTree::~AVLTree()
{
}
