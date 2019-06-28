%option noyywrap
%{
#include"parser.tab.h"
#define YY_DECL int yylex()
%}



%%
[ \t]; // ignore all whitespace
"return" {
    std::printf(yytext);
    return RETURN;
};
"var" {
    std::printf(yytext);
    return VAR;
};
"int" {
    std::printf(yytext);
    //yylval = new IntType();
    return INTTYPE;
};
"float" {
    std::printf(yytext);
    //yylval = new FloatType();
    return FLOATTYPE;
};
"addr" {
    std::printf(yytext);
    //yylval = new AddrType();
    return ADDRTYPE;
};
"func" {
    std::printf(yytext);
    //yylval = new FuncType();
    return FUNCTYPE;
};
"type" {
    std::printf(yytext);
    //yylval = new TypeType();
    return TYPETYPE;
};
"trait" {
    std::printf(yytext);
    return TRAIT;
};
"array" {
    std::printf(yytext);
    return ARRAY;
};
"tuple" {
    std::printf(yytext);
    return TUPLE;
};
"cast" {
    std::printf(yytext);
    return CAST;
};
"if" {
    std::printf(yytext);
    return IF;
};
"else" {
    std::printf(yytext);
    return ELSE;
};
"while" {
    std::printf(yytext);
    return WHILE;
};
        
"==" {
    std::printf(yytext);
    return EQ;
};
"<" {
    std::printf(yytext);
    return LT;
};
">" {
    std::printf(yytext);
    return GT;
};
"<=" {
    std::printf(yytext);
    return LE;
};
">=" {
    std::printf(yytext);
    return GE;
};
"!=" {
    std::printf(yytext);
    return NE;
};
        
"=" {
    std::printf(yytext);
    return ASSIGN;
};
"<-" {
    std::printf(yytext);
    return LASSIGN;
};
"->" {
    std::printf(yytext);
    return RASSIGN;
};
"+" {
    std::printf(yytext);
    return ADD;
};
"-" {
    std::printf(yytext);
    return SUB;
};
"*" {
    std::printf(yytext);
    return MUL;
};
"/" {
    std::printf(yytext);
    return DIV;
};
"%" {
    std::printf(yytext);
    return REM;
};
        
"(" {
    std::printf(yytext);
    return LPAREN;
};
")" {
    std::printf(yytext);
    return RPAREN;
};
"{" {
    std::printf(yytext);
    return LCURLY;
};
"}" {
    std::printf(yytext);
    return RCURLY;
};
"[" {
    std::printf(yytext);
    return LBRACKET;
};
"]" {
    std::printf(yytext);
    return RBRACKET;
};
":" {
    std::printf(yytext);
    return COLON;
};
";" {
    std::printf(yytext);
    return SEPARATOR;
};
"," {
    std::printf(yytext);
    return SEPARATOR;
};

-?[1-9][0-9]+ {
    std::printf(yytext);
    //yylval = new IntLiteral(std::stoi(yytext));
    return INTLITERAL;
};
-?[1-9][0-9]+.[0-9]+(e-?[1-9][0-9]+)? {
    std::printf(yytext);
    //yylval = new FloatLiteral(std::stof(yytext));
    return FLOATLITERAL;
};
0[xX][0-9]+ {
    std::printf(yytext);
    yylval = new AddrLiteral(std::stoul(yytext));
    return ADDRLITERAL;
};
[a-zA-Z_][0-9a-zA-Z_]+ {
    std::printf(yytext);
    yylval = new Identifier(yytext);
    return IDENTIFIER;
};



%%
