%{
#include<vector>
class ast {
public:
    ast() {}
    virtual ~ast() {}
};
class ast_int: public ast {
public:
    ast_int(int value)
};



%}

%token RETURN
%token VAR
%token INT
%token FLOAT
%token ADDR
%token ARRAY
%token TUPLE
%token TYPE
%token CAST
%token IF
%token ELSE
%token WHILE
%token EQ
%token LT
%token GT
%token LE
%token GE
%token NE
%token ASSIGN
%token LASSIGN
%token RASSIGN
%token ADD
%token SUB
%token MUL
%token DIV
%token REM
%token LPAREN
%token RPAREN
%token LCURLY
%token RCURLY
%token LBRACKET
%token RBRACKET
%token COLON
%token SEPARATOR
%token INTLITERAL
%token FLOATLITERAL
%token ADDRLITERAL
%token IDENTIFIER
%%

Type: INT
    | FLOAT
    | ADDR
    | ARRAY LBRACKET Type SEPARATOR Expr RBRACKET
    | TUPLE LBRACKET Tuple RBRACKET;
// tuple of var names and their types
Tuple: /*EMPTY*/
    | IDENTIFIER COLON Type
    | Tuple SEPARATOR IDENTIFIER COLON Type;

Operator: EQ | LT | GT | LE | GE | NE
        | ADD | SUB | MUL | DIV | REM
        | ASSIGN | LASSIGN;

// tuple of values
TupleValue: LPAREN ExprList RPAREN;
ExprList: /*EMPTY*/
    | Expr
    | ExprList SEPARATOR Expr;
// binary expression
BinExpr: Expr Operator Expr;
// function call or array indexing
Index: IDENTIFIER LPAREN ExprList RPAREN;
// return statement
Return: RETURN Expr SEPARATOR;
// var declaration
VarDecl: VAR IDENTIFIER COLON Type EQ Expr;
// code block
Block: LCURLY ExprList RCURLY;
// braching
IfElse: IF LPAREN Expr RPAREN Expr Else;
Else: /*EMPTY*/
    | ELSE Expr;
// looping
While: WHILE LPAREN Expr RPAREN Expr;
// lambda expression
Lambda: LPAREN Tuple RPAREN RASSIGN Type Expr;

Expr:
    | IDENTIFIER
    | INTLITERAL
    | FLOATLITERAL
    | ADDRLITERAL
    | TupleValue
    | SUB Expr
    | MUL Expr
    | BinExpr
    | Index
    | Return
    | VarDecl
    | Block
    | IfElse
    | While
    | Lambda;
%%
