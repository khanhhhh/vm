#ifndef _AST_HH_
#define _AST_HH_
#include<vector>
#include<string>
#include<cstring>
struct Node {
    static std::vector<Node*> all_nodes;
    Node *left;
    Node *right;
    Node(Node *left, Node *right):
        left(left),
        right(right)
    {
        all_nodes.push_back(this);
    }
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
union YYSTYPE {
    Node *node;
    int integer;
    std::string string;
    YYSTYPE() {}
    YYSTYPE(const YYSTYPE& obj) {
        std::memcpy(this, &obj, sizeof(YYSTYPE));
    }
    YYSTYPE& operator=(const YYSTYPE& obj) {
        std::memcpy(this, &obj, sizeof(YYSTYPE));
        return *this;
    }
    ~YYSTYPE() {};
};
#endif