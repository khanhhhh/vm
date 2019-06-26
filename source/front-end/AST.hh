#ifndef _AST_HH_
#define _AST_HH_
#include<vector>
#include<cstdint>
#include<string>
struct Expr {};
struct ExprList: public Expr {
    std::vector<Expr*> elements;
};
struct Identifier:  public Expr {
    std::string name;
    Identifier(const std::string& name): name(name) {}
};
struct Literal:     public Expr {};
struct IntLiteral:  public Literal {
    int32_t value;
    IntLiteral(int32_t value): value(value) {}
};
struct FloatLiteral: public Literal {
    float value;
    FloatLiteral(float value): value(value) {}
};
struct TupleValue:  public Expr {
    ExprList *list;
    TupleValue(ExprList *list): list(list) {}
};
struct Type:        public Expr {};
struct IntType:     public Type {};
struct FloatType:   public Type {};
struct AddrType:    public Type {};
struct ArrayType:   public Type {
    Type *type;
    Expr *count;
    ArrayType(Type *type, Expr *count): type(type), count(count) {}
};
struct TuplePair {
    Identifier *name; Type *type;
    TuplePair(Identifier *name, Type *type): name(name), type(type) {}
    };
struct TupleList: public Expr {
    std::vector<TuplePair> elements;
};
struct TupleType:   public Type {
    TupleList *list;
    TupleType(TupleList *list): list(list) {}
};
struct UnaryExpr:   public Expr {
    Expr *expr;
};
struct DerefExpr:   public UnaryExpr {};
struct NegExpr:     public UnaryExpr {};
struct BinaryExpr:  public Expr {
    Expr *left;
    Expr *right;
};
struct EQExpr: public BinaryExpr {};
struct LTExpr: public BinaryExpr {};
struct GTExpr: public BinaryExpr {};
struct LEExpr: public BinaryExpr {};
struct GEExpr: public BinaryExpr {};
struct NEExpr: public BinaryExpr {};
struct AddExpr: public BinaryExpr {};
struct SubExpr: public BinaryExpr {};
struct MulExpr: public BinaryExpr {};
struct DivExpr: public BinaryExpr {};
struct RemExpr: public BinaryExpr {};
struct AssignExpr: public BinaryExpr {};
struct LAssignExpr: public BinaryExpr {};

struct Index: public Expr {
    Identifier *name;
    TupleValue *arugment;
};
struct Return: public Expr {
    Expr *expr;
};
struct ValDecl: public Expr {
    Identifier *var;
    Type *type;
    Expr *value;
};
struct Block: public Expr {
    ExprList *list;
};
struct IfElse: public Expr {
    Expr *condition;
    Expr *thenExpr;
    Expr *elseExpr;
};
struct While: public Expr {
    Expr *condition;
    Expr *task;
};
struct Lambda: public Expr {
    TupleType *parameters;
    TupleType *output;
    Expr *body;
};
#endif