struct Node {
    Node *left;
    Node *right;
    Node(Node *left, Node *right):
        left(left),
        right(right)
    {}
};
struct Sum: public Node {
    Sum(Node *left, Node *right):
        Node(left, right)
    {}
};
struct Number: public Node {
    int value;
    Number(int value):
        Node(nullptr, nullptr),
        value(value)
    {}
};