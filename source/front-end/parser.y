%{
#include"AST.h"
#include<cstdio>
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
%token EOF
%%
// tuple of values
// abstract Literal
Literal:
      Identifier
    | IntLiteral
    | FloatLiteral
    | TupleValue;
Identifier: IDENTIFIER;
IntLiteral: INTLITERAL;
FloatLiteral: FLOATLITERAL;
TupleValue: LPAREN ExprList RPAREN;
// abstract Type
Type:
      IntType
    | FloatType
    | AddrType
    | ArrayType
    | TupleType;
IntType: INT;
FloatType: FLOAT;
AddrType: ADDRLITERAL;
ArrayType: ARRAY LBRACKET Type SEPARATOR Expr RBRACKET;
TupleType: TUPLE LBRACKET TupleList RBRACKET;
// Tuple list is used both in declaration and Lambda Expr
TupleList:
      /*EMPTY*/
    | Identifier COLON Type
    | TupleList SEPARATOR IDENTIFIER COLON Type;
// unary expression
UnaryExpr:
      DerefExpr
    | NegExpr;
DerefExpr: MUL Expr;
NegExpr: SUB Expr;
// binary expression
BinaryExpr:
      EQExpr
    | LTExpr
    | GTExpr
    | LEExpr
    | GEExpr
    | NEExpr
    | AddExpr
    | SubExpr
    | MulExpr
    | DivExpr
    | RemExpr
    | AssignExpr
    | LAssignExpr;
EQExpr: Expr EQ Expr;
LTExpr: Expr LT Expr;
GTExpr: Expr GT Expr;
LEExpr: Expr LE Expr;
GEExpr: Expr GE Expr;
NEExpr: Expr NE Expr;
AddExpr: Expr ADD Expr;
SubExpr: Expr SUB Expr;
MulExpr: Expr MUL Expr;
DivExpr: Expr DIV Expr;
RemExpr: Expr REM Expr;
AssignExpr: Expr ASSIGN Expr;
LAssignExpr: Expr LASSIGN Expr; 
// function call or array indexing
Index: Identifier LPAREN TupleValue RPAREN;
// return statement
Return: RETURN Expr SEPARATOR;
// var declaration
VarDecl: VAR Identifier COLON Type EQ Expr;
// code block
Block: LCURLY ExprList RCURLY;
// braching
IfElse: IF LPAREN Expr RPAREN Expr ELSE Expr
    | IF LPAREN Expr RPAREN Expr;
// looping
While: WHILE LPAREN Expr RPAREN Expr;
// lambda expression
Lambda: LPAREN TupleList RPAREN RASSIGN LPAREN TupleList RPAREN Expr;

Expr:
      /*EMPTY*/
    | Literal
    | Type
    | UnaryExpr
    | BinaryExpr
    | Index
    | Return
    | VarDecl
    | Block
    | IfElse
    | While
    | Lambda;
ExprList:
      Expr
    | ExprList SEPARATOR Expr;
%%
