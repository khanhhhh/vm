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
    virtual ~Expr() {}
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
    virtual ~Program() {
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
    virtual ~TuplePair() {
        delete type;
    }
};
struct TupleList: Expr {
    std::vector<TuplePair> elements;
    TupleList():
        Expr()
    {}
    virtual void push_element(const std::string& name, Type *type) {
        elements.emplace_back(name, type);
    }
    virtual ~TupleList() {}
};
struct ExprList: Expr {
    std::vector<Expr*> elements;
    ExprList():
        Expr()
    {}
    virtual void push_element(Expr* expr) {
        elements.push_back(expr);
    }
    virtual ~ExprList() {
        for (size_t i=0; i<elements.size(); i++) {
            delete elements[i];
        }
    }
};
struct Literal: Expr {
    Literal():
        Expr()
    {}
    virtual ~Literal() {}
};
struct Identifier: Literal {
    std::string value;
    Identifier(const char* value):
        Literal(),
        value(value)
    {}
    virtual ~Identifier() {}
};
struct IntLiteral: Literal {
    int32_t value;
    IntLiteral(int32_t value):
        Literal(),
        value(value)
    {}
    virtual ~IntLiteral() {}
};
struct FloatLiteral: Literal {
    float value;
    FloatLiteral(float value):
        Literal(),
        value(value)
    {}
    virtual ~FloatLiteral() {}
};
struct AddrLiteral: Literal {
    uint32_t value;
    AddrLiteral(uint32_t value):
        Literal(),
        value(value)
    {}
    virtual ~AddrLiteral() {}
};
struct TupleLiteral: Literal {
    ExprList* list;
    TupleLiteral(ExprList* list):
        Literal(),
        list(list)
    {}
    virtual ~TupleLiteral() {
        delete list;
    }
};
struct Type: Expr {
    Type():
        Expr()
    {}
    virtual ~Type() {}
};
struct TypeType: Type {
    TypeType():
        Type()
    {}
    virtual ~TypeType() {}
};
struct FuncType: Type {
    FuncType():
        Type()
    {}
    virtual ~FuncType() {}
};
struct IntType: Type {
    IntType():
        Type()
    {}
    virtual ~IntType() {}
};
struct FloatType: Type {
    FloatType():
        Type()
    {}
    virtual ~FloatType() {}
};
struct AddrType: Type {
    AddrType():
        Type()
    {}
    virtual ~AddrType() {}
};
struct TupleType: Type {
    TupleList *list;
    TupleType(TupleList* list):
        Type(),
        list(list)
    {}
    virtual ~TupleType() {
        delete list;
    }
};

struct UnaryExpr: Expr {
    Expr *element;
    UnaryExpr(Expr *element):
        Expr(),
        element(element)
    {}
    virtual ~UnaryExpr() {
        delete element;
    }
};
struct DerefExpr: UnaryExpr {
    DerefExpr(Expr *element):
        UnaryExpr(element)
    {}
    virtual ~DerefExpr() {}
};
struct NegExpr: UnaryExpr {
    NegExpr(Expr *element):
        UnaryExpr(element)
    {}
    virtual ~NegExpr() {}
};
struct BinaryExpr: Expr {
    Expr *left;
    Expr *right;
    BinaryExpr(Expr *left, Expr *right):
        Expr(),
        left(left),
        right(right)
    {}
    virtual ~BinaryExpr() {
        delete left;
        delete right;
    }
};
struct EQExpr: BinaryExpr {
    EQExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~EQExpr() {}
};
struct LTExpr: BinaryExpr {
    LTExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~LTExpr() {}
};
struct GTExpr: BinaryExpr {
    GTExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~GTExpr() {}
};
struct LEExpr: BinaryExpr {
    LEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~LEExpr() {}
};
struct GEExpr: BinaryExpr {
    GEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~GEExpr() {}
};
struct NEExpr: BinaryExpr {
    NEExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~NEExpr() {}
};
struct AddExpr: BinaryExpr {
    AddExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~AddExpr() {}
};
struct SubExpr: BinaryExpr {
    SubExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~SubExpr() {}
};
struct MulExpr: BinaryExpr {
    MulExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~MulExpr() {}
};
struct DivExpr: BinaryExpr {
    DivExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~DivExpr() {}
};
struct RemExpr: BinaryExpr {
    RemExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~RemExpr() {}
};
struct AssignExpr: BinaryExpr {
    AssignExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~AssignExpr() {}
};
struct LAssignExpr: BinaryExpr {
    LAssignExpr(Expr *left, Expr *right):
        BinaryExpr(left, right)
    {}
    virtual ~LAssignExpr() {}
};
struct Index: Expr {
    Identifier *identifier;
    TupleLiteral *arguments;
    Index(Identifier* identifier, TupleLiteral *arguments):
        Expr(),
        identifier(identifier),
        arguments(arguments)
    {}
    virtual ~Index() {
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
    virtual ~Return() {
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
    virtual ~VarDecl() {
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
    virtual ~Block() {
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
    virtual ~IfElse() {
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
    virtual ~While() {
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
    virtual ~Lambda() {
        delete type_in;
        delete type_out;
        delete body;
    }
};
#endif