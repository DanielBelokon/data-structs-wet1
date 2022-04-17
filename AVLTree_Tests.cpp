#include "AVLTree.h"
#include <iostream>
#include <string>

typedef struct dummy_struct
{
    int id;
    int salary;
    friend std::ostream &operator<<(std::ostream &out, const dummy_struct &data);
    bool operator<(const dummy_struct &other) const
    {
        return id < other.id;
    }
} dummy_struct;

std::ostream &operator<<(std::ostream &out, const dummy_struct &data)
{
    out << "i: " << data.id << " s: " << data.salary << std::endl;
    return out;
}

bool compare(const dummy_struct &a, const dummy_struct &b)
{
    if (a.salary > b.salary)
    {
        return true;
    }
    else
        return a.id < b.id;
}

struct Trunk
{
    Trunk *prev;
    std::string str;

    Trunk(Trunk *prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
    {
        return;
    }

    showTrunks(p->prev);
    std::cout << p->str;
}

void printTree(Node<dummy_struct> *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
    {
        return;
    }

    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getRight(), trunk, true);

    if (!prev)
    {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`———";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    std::cout << " " << root->getData() << std::endl;

    if (prev)
    {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->getLeft(), trunk, false);
}

int main()
{
    AVLTree<dummy_struct> tree;
    tree.add({1, 100});
    tree.add({2, 200});
    tree.add({3, 140});
    tree.add({4, 120});
    tree.add({6, 100});
    tree.add({99, 150});
    tree.add({7, 1004});
    tree.add({55, 2003});
    tree.add({10, 100});
    tree.add({51, 1001});
    tree.add({14, 100});
    printTree(tree.getRoot(), nullptr, false);
}