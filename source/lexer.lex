%{
#include<vector>
#include<string>
#include<cstdio>
    enum token_type {
        RETURN,
        VAR,
        INT,
        FLOAT,
        ADDR,
        ARRAY,
        TUPLE,
        TYPE,
        CAST,
        IF,
        ELSE,
        WHILE,
        EQ,
        LT,
        GT,
        LE,
        GE,
        NE,
        ASSIGN,
        LASSIGN,
        RASSIGN,
        ADD,
        SUB,
        MUL,
        DIV,
        REM,
        LPAREN,
        RPAREN,
        LCURLY,
        RCURLY,
        LBRACKET,
        RBRACKET,
        COLON,
        SEMICOLON,
        COMMA,
        INTLITERAL,
        FLOATLITERAL,
        ADDRLITERAL,
        IDENTIFIER
    };
class token {
public:
    token_type type;
    std::string lexeme;
    token(token_type type, const std::string& lexeme = ""):
        type(type), lexeme(lexeme)
    {}
    ~token() {}
};
std::vector<token> tokens;
%}



%%
"return"    {tokens.emplace_back(RETURN);}
"var"       {tokens.emplace_back(VAR);}
"int"       {tokens.emplace_back(INT);}
"float"     {tokens.emplace_back(FLOAT);}
"addr"      {tokens.emplace_back(ADDR);}
"array"     {tokens.emplace_back(ARRAY);}
"tuple"     {tokens.emplace_back(TUPLE);}
"type"      {tokens.emplace_back(TYPE);}
"cast"      {tokens.emplace_back(CAST);}
"if"        {tokens.emplace_back(IF);}
"else"      {tokens.emplace_back(ELSE);}
"while"     {tokens.emplace_back(WHILE);}

"=="        {tokens.emplace_back(EQ);}
"<"         {tokens.emplace_back(LT);}
">"         {tokens.emplace_back(GT);}
"<="        {tokens.emplace_back(LE);}
">="        {tokens.emplace_back(GE);}
"!="        {tokens.emplace_back(NE);}

"="         {tokens.emplace_back(ASSIGN);}
"<-"        {tokens.emplace_back(LASSIGN);}
"->"        {tokens.emplace_back(RASSIGN);}
"+"         {tokens.emplace_back(ADD);}
"-"         {tokens.emplace_back(SUB);}
"*"         {tokens.emplace_back(MUL);}
"/"         {tokens.emplace_back(DIV);}
"%"         {tokens.emplace_back(REM);}

"("         {tokens.emplace_back(LPAREN);}
")"         {tokens.emplace_back(RPAREN);}
"{"         {tokens.emplace_back(LCURLY);}
"}"         {tokens.emplace_back(LCURLY);}
"["         {tokens.emplace_back(LBRACKET);}
"]"         {tokens.emplace_back(RBRACKET);}
":"         {tokens.emplace_back(COLON);}
";"         {tokens.emplace_back(SEMICOLON);}
","         {tokens.emplace_back(COMMA);}

-?[1-9][0-9]+                               {tokens.emplace_back(INTLITERAL, yytext);}
-?[1-9][0-9]+.[0-9]+(e-?[1-9][0-9]+)?       {tokens.emplace_back(FLOATLITERAL, yytext);}
0[xX][0-9]+                                 {tokens.emplace_back(ADDRLITERAL, yytext);}
[a-zA-Z_][0-9a-zA-Z_]+                      {tokens.emplace_back(IDENTIFIER, yytext);}

%%
int yywrap(){return 1;}