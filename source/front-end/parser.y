%code requires {
#include<AST.hh>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
}
%{

%}

%token RETURN
%token VAR
%token IntType
%token FloatType
%token AddrType
%token ARRAY
%token TUPLE
%token TypeType
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
%token IntLiteral
%token FloatLiteral
%token AddrLiteral
%token Identifier
%%
Program:
    ExprList;
// tuple of values
// abstract Literal
TupleList:
    /*EMPTY*/
|   Identifier COLON Type
|   TupleList SEPARATOR Identifier COLON Type;
ExprList:
    /*EMPTY*/
|   Expr
|   ExprList SEPARATOR Expr;
Literal:
    Identifier
|   IntLiteral
|   FloatLiteral
|   AddrLiteral
|   TupleLiteral;
TupleLiteral: LPAREN ExprList RPAREN;
// abstract Type
Type:
|   FloatType
|   AddrType
|   ArrayType
|   TupleType;
ArrayType: ARRAY LBRACKET Type SEPARATOR Expr RBRACKET;
TupleType: TUPLE LBRACKET TupleList RBRACKET;
// Tuple list is used both in declaration and Lambda Expr
// unary expression
UnaryExpr:
    DerefExpr
|   NegExpr;
DerefExpr: MUL Expr;
NegExpr: SUB Expr;
// binary expression
BinaryExpr:
    EQExpr
|   LTExpr
|   GTExpr
|   LEExpr
|   GEExpr
|   NEExpr
|   AddExpr
|   SubExpr
|   MulExpr
|   DivExpr
|   RemExpr
|   AssignExpr
|   LAssignExpr;
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
Index: Identifier TupleLiteral;
// return statement
Return: RETURN Expr SEPARATOR;
// var declaration
VarDecl: VAR Identifier COLON Type EQ Expr;
// code block
Block: LCURLY ExprList RCURLY;
// braching
IfElse:
    IF LPAREN Expr RPAREN Expr ELSE Expr
|   IF LPAREN Expr RPAREN Expr;
// looping
While: WHILE LPAREN Expr RPAREN Expr;
// lambda expression
Lambda: Type RASSIGN Type Expr;

Expr:
    Literal
|   Type
|   UnaryExpr
|   BinaryExpr
|   Index
|   Return
|   VarDecl
|   Block
|   IfElse
|   While
|   Lambda;
%%
