#ifndef _AST_HH_
#define _AST_HH_
#include<cstdint>
#include<string>
#include<vector>


#define YYSTYPE_IS_DECLARED
struct Expr;
typedef Expr* YYSTYPE;

struct Expr {
    Expr() {}
    ~Expr() {}
};
struct ExprList;
struct Program: Expr {
    static Program* program;
    ExprList *list;
    Program(ExprList* list):
        Expr(),
        list(list)
    {
        program = this;
    }
    ~Program() {
        delete list;
    }
};
struct Type;
struct TuplePair {
    std::string name;
    Type *type;
    TuplePair(const std::string& name, Type *type):
        name(name),
        type(type)
    {}
    ~TuplePair() {
        delete type;
    }
};
struct TupleList: Expr {
    std::vector<TuplePair> elements;
    TupleList():
        Expr()
    {}
    void push_element(const std::string& name, Type *type) {
        elements.emplace_back(name, type);
    }
    ~TupleList() {}
};
struct ExprList: Expr {
    std::vector<Expr*> elements;
    ExprList():
        Expr()
    {}
    void push_element(Expr* expr) {
        elements.push_back(expr);
    }
    ~ExprList() {
        for (size_t i=0; i<elements.size(); i++) {
            delete elements[i];
        }
    }
};
struct Literal: Expr {
    Literal():
        Expr()
    {}
    ~Literal() {}
};
struct Identifier: Literal {
    std::string value;
    Identifier(const char* value):
        Literal(),
        value(value)
    {}
    ~Identifier() {}
};
struct IntLiteral: Literal {
    int32_t value;
    IntLiteral(int32_t value):
        Literal(),
        value(value)
    {}
    ~IntLiteral() {}
};
struct FloatLiteral: Literal {
    float value;
    FloatLiteral(float value):
        Literal(),
        value(value)
    {}
    ~FloatLiteral() {}
};
struct AddrLiteral: Literal {
    uint32_t value;
    AddrLiteral(uint32_t value):
        Literal(),
        value(value)
    {}
    ~AddrLiteral() {}
};
struct TupleLiteral: Literal {
    ExprList* list;
    TupleLiteral(ExprList* list):
        Literal(),
        list(list)
    {}
    ~TupleLiteral() {
        delete list;
    }
};
struct Type: Expr {
    Type():
        Expr()
    {}
    ~Type() {}
};
struct TypeType: Type {
    TypeType():
        Type()
    {}
    ~TypeType() {}
};
struct IntType: Type {
    IntType():
        Type()
    {}
    ~IntType() {}
};
struct FloatType: Type {
    FloatType():
        Type()
    {}
    ~FloatType() {}
};
struct AddrType: Type {
    AddrType():
        Type()
    {}
    ~AddrType() {}
};
struct TupleType: Type {
    TupleList *list;
    TupleType(TupleList* list):
        Type(),
        list(list)
    {}
    ~TupleType() {
        delete list;
    }
};

struct UnaryExpr: Expr {
    Expr *element;
    UnaryExpr(Expr *element):
        Expr(),
        element(element)
    {}
    ~UnaryExpr() {
        delete element;
    }
};
struct DerefExpr: UnaryExpr {
    DerefExpr(Expr *element):
        UnaryExpr(element)
    {}
    ~DerefExpr() {}
};
struct NegExpr: UnaryExpr {
    NegExpr(Expr *element):
        UnaryExpr(element)
    {}
    ~NegExpr() {}
};
struct BinaryExpr: Expr {
    Expr *left;
    Expr *right;
    BinaryExpr(Expr *left, Expr *right):
        Expr(),
        left(left),
        right(right)
    {}
    ~BinaryExpr() {
        delete left;
        delete right;
    }
};
struct EQExpr: BinaryExpr {
    EQExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~EQExpr() {}
};
struct LTExpr: BinaryExpr {
    LTExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~LTExpr() {}
};
struct GTExpr: BinaryExpr {
    GTExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~GTExpr() {}
};
struct LEExpr: BinaryExpr {
    LEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~LEExpr() {}
};
struct GEExpr: BinaryExpr {
    GEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~GEExpr() {}
};
struct NEExpr: BinaryExpr {
    NEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~NEExpr() {}
};
struct AddExpr: BinaryExpr {
    AddExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~AddExpr() {}
};
struct SubExpr: BinaryExpr {
    SubExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~SubExpr() {}
};
struct MulExpr: BinaryExpr {
    MulExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~MulExpr() {}
};
struct DivExpr: BinaryExpr {
    DivExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~DivExpr() {}
};
struct RemExpr: BinaryExpr {
    RemExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~RemExpr() {}
};
struct AssignExpr: BinaryExpr {
    AssignExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~AssignExpr() {}
};
struct LAssignExpr: BinaryExpr {
    LAssignExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    ~LAssignExpr() {}
};
struct Index: Expr {
    Identifier *identifier;
    TupleLiteral *arguments;
    Index(Identifier* identifier, TupleLiteral *arguments):
        Expr(),
        identifier(identifier),
        arguments(arguments)
    {}
    ~Index() {
        delete identifier;
        delete arguments;
    }
};
struct Return: Expr {
    Expr *expr;
    Return(Expr* expr):
        Expr(),
        expr(expr)
    {}
    ~Return() {
        delete expr;
    }
};
struct VarDecl: Expr {
    Identifier *identifier;
    Type *type;
    Expr *expr;
    VarDecl(Identifier* identifier, Type* type, Expr* expr):
        Expr(),
        identifier(identifier),
        type(type),
        expr(expr)
    {}
    ~VarDecl() {
        delete identifier;
        delete type;
        delete expr;
    }
};
struct Block: Expr {
    ExprList* list;
    Block(ExprList* list):
        Expr(),
        list(list)
    {}
    ~Block() {
        delete list;
    }
};
struct IfElse: Expr {
    Expr* condition;
    Expr* then_expr;
    Expr* else_expr;
    IfElse(Expr* condition, Expr* then_expr, Expr* else_expr):
        Expr(),
        condition(condition),
        then_expr(then_expr),
        else_expr(else_expr)
    {}
    ~IfElse() {
        delete condition;
        delete then_expr;
        delete else_expr;
    }
};
struct While: Expr {
    Expr* condition;
    Expr* task;
    While(Expr* condition, Expr* task):
        Expr(),
        condition(condition),
        task(task)
    {}
    ~While() {
        delete condition;
        delete task;
    }
};
struct Lambda: Expr {
    Type* type_in;
    Type* type_out;
    Expr* body;
    Lambda(Type* type_in, Type* type_out, Expr* body):
        Expr(),
        type_in(type_in),
        type_out(type_out),
        body(body)
    {}
    ~Lambda() {
        delete type_in;
        delete type_out;
        delete body;
    }
};
#endif