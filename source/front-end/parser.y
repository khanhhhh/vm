%code requires {
#include<AST.hh>
#include<cstdio>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
}
%{

%}

%token EoF
%token RETURN
%token VAR
%token INTTYPE
%token FLOATTYPE
%token ADDRTYPE
%token FUNCTYPE
%token TYPETYPE
%token ARRAY
%token TUPLE
%token TRAIT
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
Program:
    ExprList EoF;
// tuple of values
// abstract Literal
TupleList:
    /*EMPTY*/
|   IDENTIFIER COLON Type
|   TupleList SEPARATOR IDENTIFIER COLON Type;
ExprList:
    /*EMPTY*/
|   Expr
|   ExprList SEPARATOR Expr;
Literal:
    IDENTIFIER
|   INTLITERAL
|   FLOATLITERAL
|   ADDRLITERAL
|   TupleLiteral;
TupleLiteral: LPAREN ExprList RPAREN;
// abstract Type
Type:
    INTTYPE
|   FLOATTYPE
|   ADDRTYPE
|   FUNCTYPE
|   ArrayType
|   TupleType
|   TraitType;
ArrayType: ARRAY LBRACKET Type SEPARATOR Expr RBRACKET;
TupleType: TUPLE LBRACKET TupleList RBRACKET;
TraitType: TRAIT LBRACKET IDENTIFIER RBRACKET;
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
Index: IDENTIFIER TupleLiteral;
// return statement
Return: RETURN Expr SEPARATOR;
// var declaration
VarDecl: VAR IDENTIFIER COLON Type EQ Expr;
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
void yyerror(const char* s) {
	std::fprintf(stderr, "Parse error: %s\n", s);
}