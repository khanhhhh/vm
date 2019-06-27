#ifndef _AST_HH_
#define _AST_HH_
#include<vector>
#include<string>
#include<cstring>
#include<cstdio>
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
typedef union somename{
    Node *node;
    int integer;
    std::string string;
    somename() {}
    somename(const somename& obj) {
        std::memcpy(this, &obj, sizeof(somename));
    }
    somename& operator=(const somename& obj) {
        std::memcpy(this, &obj, sizeof(somename));
        return *this;
    }
    ~somename() {};
} YYSTYPE;
#endif