Type = INT
    | FLOAT
    | ADDR
    | ARRAY LBRACKET Type RBRACKET

Value = INDENTIFIER
    | INTLITERAL
    | FLOATLITERAL
    | ADDRLITERAL

Operator = EQ | LT | GT | LE | GE | NE
        | ADD | SUB | MUL | DIV | REM

Expr = Expr Operator Value
    | Value LPAREN Tuple RPAREN

Tuple = INDENTIFIER COLON Type TupleTail
TupleTail = COMMA Tuple


VarDecl = VAR INDENTIFIER COLON Type EQ Expr SEMICOLON
Return = RETURN SEMICOLON
    ! RETURN Value SEMICOLON