

template <class T>
class Node
{
private:
    T data;
    Node<T> *left;
    Node<T> *right;

    int balance_factor;

public:
    Node(T data) : data(data) {}
    Node() = default;

    int getBf() { return balance_factor; }
    T getData() { return data; }
    const T getData() const { return data; }
    Node<T> *getLeft() { return left; }
    Node<T> *getRight() { return right; }
    void setLeft(Node &node) { left = &node; }
    void setRight(Node &node) { right = &node; }
};
