%{
    #include"AST.hh"
    #include<string>
    struct Node {
        Expr *expr;
        std::string string;
    };
    #define YYSTYPE Node
    int yylex(void);
%}
%token<string> RETURN
%token<string> VAR
%token<string> INT
%token<string> FLOAT
%token<string> ADDR
%token<string> ARRAY
%token<string> TUPLE
%token<string> TYPE
%token<string> CAST
%token<string> IF
%token<string> ELSE
%token<string> WHILE
%token<string> EQ
%token<string> LT
%token<string> GT
%token<string> LE
%token<string> GE
%token<string> NE
%token<string> ASSIGN
%token<string> LASSIGN
%token<string> RASSIGN
%token<string> ADD
%token<string> SUB
%token<string> MUL
%token<string> DIV
%token<string> REM
%token<string> LPAREN
%token<string> RPAREN
%token<string> LCURLY
%token<string> RCURLY
%token<string> LBRACKET
%token<string> RBRACKET
%token<string> COLON
%token<string> SEPARATOR
%token<string> INTLITERAL
%token<string> FLOATLITERAL
%token<string> ADDRLITERAL
%token<string> IDENTIFIER

%type<expr> ExprList
%type<expr> Literal
%type<expr> Identifier
%type<expr> IntLiteral
%type<expr> FloatLiteral
%type<expr> TupleValue
%type<expr> Type
%type<expr> IntType
%type<expr> FloatType
%type<expr> AddrType
%type<expr> ArrayType
%type<expr> TupleType
%type<expr> TupleList
%type<expr> UnaryExpr
%type<expr> DerefExpr
%type<expr> NegExpr
%type<expr> BinaryExpr
%type<expr> EQExpr
%type<expr> LTExpr
%type<expr> GTExpr
%type<expr> LEExpr
%type<expr> GEExpr
%type<expr> NEExpr
%type<expr> AddExpr
%type<expr> SubExpr
%type<expr> MulExpr
%type<expr> DivExpr
%type<expr> RemExpr
%type<expr> AssignExpr
%type<expr> LAssignExpr
%type<expr> Index
%type<expr> Return
%type<expr> VarDecl
%type<expr> Block
%type<expr> IfElse
%type<expr> While
%type<expr> Lambda
%type<expr> Expr


//%token<string> EOF
%%
ExprList[obj]:
    /*EMPTY*/ {
        $obj = new ExprList;
    }
|   Expr[expr] {
        $obj = new ExprList;
        $obj->elements.push_back(expr);
    }
|   ExprList[left] SEPARATOR Expr[expr] {
        $obj = new ExprList;
        $obj->elements = std::move(left.elements);
        $obj->elements.push_back(expr);
        delete left;
    };
// tuple of values
// abstract Literal
Literal[obj]:
    Identifier[child] {
        $obj = child;
    }
|   IntLiteral[child] {
        $obj = child;
    }
|   FloatLiteral[child] {
        $obj = child;
    }
|   TupleValue[child] {
        $obj = child;
    };
Identifier[obj]: IDENTIFIER[name] {
    $obj = new Identifier({name});
};
IntLiteral[obj]: INTLITERAL[name] {
    $obj = new IntLiteral({std::stoi(name)});
};
FloatLiteral[obj]: FLOATLITERAL[name] {
    $obj = new FloatLiteral({std::stof(name)});
};
TupleValue[obj]: LPAREN ExprList[child] RPAREN {
    $obj = new TupleValue({child});
};
// abstract Type
Type[obj]:
    IntType[child] {
        $obj = child;
    }
|   FloatType[child] {
        $obj = child;
    }
|   AddrType[child] {
        $obj = child;
    }
|   ArrayType[child] {
        $obj = child;
    }
|   TupleType[child] {
        $obj = child;
    };
IntType[obj]: INT[name] {
    $obj = new IntType;
};
FloatType[obj]: FLOAT[name] {
    $obj = new FloatType;
};
AddrType[obj]: ADDRLITERAL[name] {
    $obj = new AddrType;
};
ArrayType[obj]: ARRAY LBRACKET Type[type] SEPARATOR Expr[count] RBRACKET {
    $obj = new ArrayType({type, count});
};
TupleType[obj]: TUPLE LBRACKET TupleList[child] RBRACKET {
    $obj = new TupleList({child});
};
// Tuple list is used both in declaration and Lambda Expr
TupleList[obj]:
    /*EMPTY*/ {
        $obj = new TupleList;
    }
|   Identifier[name] COLON Type[type] {
        $obj = new TupleList;
        $obj->elements.push_back({name, type});
    }
|   TupleList[left] SEPARATOR Identifier[name] COLON Type[type] {
        $obj = new TupleList;
        $obj->elements = std::move(left.elements);
        $obj->elements.push_back({name, type});
        delete left;
    };
// unary expression
UnaryExpr[obj]:
    DerefExpr[child] {
        $obj = child;
    }
|    NegExpr[child] {
        $obj = child;
    };
DerefExpr[obj]: MUL Expr[child] {
    $obj = new UnaryExpr({child});
};
NegExpr[obj]: SUB Expr[child] {
    $obj = new UnaryExpr({child});
};
// binary expression
BinaryExpr[obj]:
    EQExpr[child] {
        $obj = child;
    }
|   LTExpr[child] {
        $obj = child;
    }
|   GTExpr[child] {
        $obj = child;
    }
|   LEExpr[child] {
        $obj = child;
    }
|   GEExpr[child] {
        $obj = child;
    }
|   NEExpr[child] {
        $obj = child;
    }
|   AddExpr[child] {
        $obj = child;
    }
|   SubExpr[child] {
        $obj = child;
    }
|   MulExpr[child] {
        $obj = child;
    }
|   DivExpr[child] {
        $obj = child;
    }
|   RemExpr[child] {
        $obj = child;
    }
|   AssignExpr[child] {
        $obj = child;
    }
|   LAssignExpr[child] {
        $obj = child;
    };
EQExpr[obj]: Expr[left] EQ Expr[right] {
    $obj = new EQExpr({left, right});
};
LTExpr[obj]: Expr[left] LT Expr[right] {
    $obj = new LTExpr({left, right});
};
GTExpr[obj]: Expr[left] GT Expr[right] {
    $obj = new GTExpr({left, right});
};
LEExpr[obj]: Expr[left] LE Expr[right] {
    $obj = new LEExpr({left, right});
};
GEExpr[obj]: Expr[left] GE Expr[right] {
    $obj = new GEExpr({left, right});
};
NEExpr[obj]: Expr[left] NE Expr[right] {
    $obj = new NEExpr({left, right});
};
AddExpr[obj]: Expr[left] ADD Expr[right] {
    $obj = new AddExpr({left, right});
};
SubExpr[obj]: Expr[left] SUB Expr[right] {
    $obj = new SubExpr({left, right});
};
MulExpr[obj]: Expr[left] MUL Expr[right] {
    $obj = new MulExpr({left, right});
};
DivExpr[obj]: Expr[left] DIV Expr[right] {
    $obj = new DivExpr({left, right});
};
RemExpr[obj]: Expr[left] REM Expr[right] {
    $obj = new RemExpr({left, right});
};
AssignExpr[obj]: Expr[left] ASSIGN Expr[right] {
    $obj = new AssignExpr({left, right});
};
LAssignExpr[obj]: Expr[left] LASSIGN Expr[right] {
    $obj = new LAssignExpr({left, right});
};
// function call or array indexing
Index[obj]: Identifier[name] LPAREN TupleValue[arguments] RPAREN {
    $obj = new Index({name, arguments});
};
// return statement
Return[obj]: RETURN Expr[expr] SEPARATOR {
    $obj = new Return({expr});
};
// var declaration
VarDecl[obj]: VAR Identifier[var] COLON Type[type] EQ Expr[value] {
    $obj = new VarDecl({var, type, value});
};
// code block
Block[obj]: LCURLY ExprList[list] RCURLY {
    $obj = new Block({list});
};
// braching
IfElse[obj]:
    IF LPAREN Expr[condition] RPAREN Expr[thenExpr] ELSE Expr[elseExpr] {
        $obj = new IfElse({condition, thenExpr, elseExpr});
    }
|   IF LPAREN Expr[condition] RPAREN Expr[thenExpr] {
        $obj = new IfElse({condition, thenExpr, nullptr});
    };
// looping
While[obj]: WHILE LPAREN Expr[condition] RPAREN Expr[task] {
        $obj = new While({condition, task});
    };
// lambda expression
Lambda[obj]: LPAREN TupleList[parameters] RPAREN RASSIGN LPAREN TupleList[output] RPAREN Expr[body] {
    $obj = new Lambda({parameters, output, body});
};

Expr[obj]:
    Literal[child] {
        $obj = child;
    }
|   Type[child] {
        $obj = child;
    }
|   UnaryExpr[child] {
        $obj = child;
    }
|   BinaryExpr[child] {
        $obj = child;
    }
|   Index[child] {
        $obj = child;
    }
|   Return[child] {
        $obj = child;
    }
|   VarDecl[child] {
        $obj = child;
    }
|   Block[child] {
        $obj = child;
    }
|   IfElse[child] {
        $obj = child;
    }
|   While[child] {
        $obj = child;
    }
|   Lambda[child] {
        $obj = child;
    };
%%
