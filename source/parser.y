%{

%}
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
ExprtList: /*EMPTY*/
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
    | ArrayLiteral
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