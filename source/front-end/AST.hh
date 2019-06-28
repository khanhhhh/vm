#ifndef _AST_HH_
#define _AST_HH_
#define YYSTYPE_IS_DECLARED
#include<vector>
#include<string>
#include<cstdint>
struct Expr;
struct ExprList;
struct Program;
struct Literal;
struct Type;
typedef Expr* YYSTYPE;
struct Program {
    static Program* program;
    ExprList* list;
    Program(ExprList* list):
        list(list)
    {}
    ~Program() {
        delete list;
    }
};
struct ExprList {
    std::vector<Expr*> elements;
    ExprList():
        elements()
    {}
    ~ExprList() {
        for (uint32_t i = 0; i < elements.size(); i++) {
            delete elements[i];
        };
    }
    void push_element(Expr* elem) {
        elements.push_back(elem);
    }
};
struct Expr {
    Expr() {}
    ~Expr() {}
};
struct Literal: Expr {
    Literal():
        Expr()
    {}
    ~Literal() {}
};
struct Identifier: Literal {
    std::string name;
    Identifier(const char* name):
        Literal(), name(name)
    {}
    ~Identifier() {}
};
struct IntLiteral: Literal {
    int32_t value;
    IntLiteral(int32_t value):
        Literal(), value(value)
    {}
    ~IntLiteral() {}
};
struct FloatLiteral: Literal {
    float value;
    FloatLiteral(float value):
        Literal(), value(value)
    {}
    ~FloatLiteral() {}
};
struct AddrLiteral: Literal {
    uint32_t value;
    AddrLiteral(uint32_t value):
        Literal(), value(value)
    {}
    ~AddrLiteral() {}
};
struct TupleLiteral: Literal {
    ExprList *list;
    TupleLiteral(ExprList *list):
        Literal(), list(list)
    {}
    ~TupleLiteral() {}
};
struct FuncLiteral: Literal {
    Type *type_in;
    Type *type_out;
    Expr *body;
    FuncLiteral(Type* type_in, Type* type_out, Expr* body):
        Literal(), type_in(type_in), type_out(type_out)
    {}
    ~FuncLiteral() {}
};
struct FuncCall: Literal {
    Identifier* name;
    TupleLiteral* parameters;
    FuncCall(Identifier* name, TupleLiteral* arguments):
        Literal(), name(name), parameters(arguments)
    {}
    ~FuncCall() {}
};
struct Return: Literal {
    Expr* value;
    Return(Expr* value):
        Literal(), value(value)
    {}
    ~Return() {}
};
struct VarDecl: Literal {
    Identifier* name;
    Type* type;
    Expr* value;
    VarDecl(Identifier* name, Type* type, Expr* value):
        Literal(), name(name), type(type), value(value)
    {}
    ~VarDecl() {}
};
struct Block: Literal {

};

#endif
