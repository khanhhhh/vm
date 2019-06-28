%code requires {
#include<AST.hh>
#include<stdexcept>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
}
%{

%}

%token RETURN
%token VAR
%token INTTYPE
%token FLOATTYPE
%token ADDRTYPE
%token FUNCTYPE
%token TYPETYPE
%token ARRAYTYPE
%token TUPLETYPE
%token TRAITTYPE
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
    ExprList;
ExprList:
    /*empty*/
|   Expr
|   ExprList SEPARATOR Expr;

Expr:
    Literal
|   Type;

Literal:
    IDENTIFIER
|   INTLITERAL
|   FLOATLITERAL
|   ADDRLITERAL
|   TupleLiteral
|   FuncLiteral
|   FuncCall
|   Return
|   VarDecl
|   Block
|   IfElse
|   While
|   UnaryExpr
|   BinaryExpr;
TupleLiteral:
    LPAREN ExprList RPAREN;
FuncLiteral:
    Type RASSIGN Type Expr;
FuncCall:
    IDENTIFIER TupleLiteral;
Return:
    RETURN Expr SEPARATOR;
VarDecl:
    VAR IDENTIFIER COLON Type EQ Expr;
Block:
    LCURLY ExprList RCURLY;
IfElse:
    IF Expr Expr ELSE Expr
|   IF Expr Expr;
While:
    WHILE Expr Expr;
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
LAssignExpr: Expr LASSIGN Expr

Type:
    INTTYPE
|   FLOATTYPE
|   ADDRTYPE
|   FUNCTYPE
|   TYPETYPE
|   ArrayType
|   TupleType
|   TraitType;

ArrayType:
    ARRAYTYPE LBRACKET Type SEPARATOR Expr RBRACKET;
TupleType:
    TUPLETYPE LBRACKET TupleList RBRACKET;
TupleList:
    /*empty*/
|   IDENTIFIER COLON Type
|   TupleList SEPARATOR IDENTIFIER COLON Type;
TraitType:
    TRAITTYPE LBRACKET IDENTIFIER RBRACKET;


%%
void yyerror(const char* s) {
	throw std::runtime_error(std::string("ParseError: ") + s);
}
