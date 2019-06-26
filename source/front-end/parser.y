/*
Some notes about AST.
0. There are about 300 shift/reduce, reduce/reduce conficts in this grammar. Be careful =))
1. Every element in this language is a expression.
2. Program is a Expression List
3. Expression List is a list of expresions, separated by SEPARATOR (either semicolon or comma)
4. TupleValue is (1, 2, 3, 4). List of expressions enclosed by parentheses
5. TupleList is "x: typex, y: typey, ..., z: typez"
6. TupleType = TUPLE [TupleList]
7. Array = ARRAY[TYPE, SIZE]
8.  RETURN VALUE SEMICOLON has meaning of an expression (with semicolon).
    RETURN VALUE without SEMICOLON is a syntax error
9. 


*/



%{
    #include"AST.hh"
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
ExprList:
    /*EMPTY*/
|   Expr
|   ExprList SEPARATOR Expr;
// tuple of values
// abstract Literal
Literal:
    Identifier
|   IntLiteral
|   FloatLiteral
|   TupleValue
Identifier: IDENTIFIER;
IntLiteral: INTLITERAL;
FloatLiteral: FLOATLITERAL;
TupleValue: LPAREN ExprList RPAREN;
// abstract Type
Type:
|   FloatType
|   AddrType
|   ArrayType
|   TupleType;
IntType: INT;
FloatType: FLOAT;
AddrType: ADDRLITERAL;
ArrayType: ARRAY LBRACKET Type SEPARATOR Expr RBRACKET;
TupleType: TUPLE LBRACKET TupleList RBRACKET;
// Tuple list is used both in declaration and Lambda Expr
TupleList:
    /*EMPTY*/
|   Identifier COLON Type
|   TupleList SEPARATOR Identifier COLON Type;
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
Index: Identifier LPAREN TupleValue RPAREN;
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
Lambda: LPAREN TupleList RPAREN RASSIGN LPAREN TupleList RPAREN Expr;

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
