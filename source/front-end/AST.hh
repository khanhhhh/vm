#ifndef _AST_HH_
#define _AST_HH_
#include<vector>
#include<cstdint>
#include<string>
struct Expr {};
struct Identifier:  public Expr {
    std::string name;
};
struct Literal:     public Expr {};
struct IntLiteral:  public Literal {
    int32_t value;
};
struct FloatLiteral: public Literal {
    float value;
};
struct TupleValue:  public Expr {
    std::vector<Literal*> elements;
};
struct Type:        public Expr {};
struct IntType:     public Type {};
struct FloatType:   public Type {};
struct AddrType:    public Type {};
struct ArrayType:   public Type {
    Type *type;
    uint32_t count;
};
struct TuplePair {Type *type; std::string name;};
struct TupleType:   public Type {
    std::vector<TuplePair> elements;
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
struct GTExpr: public BinaryExpr {};
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
    std::vector<Expr*> elements;
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