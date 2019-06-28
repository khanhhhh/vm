%option noyywrap
%{
#include"parser.tab.h"
#define YY_DECL int yylex()
%}



%%
[ \t]	; // ignore all whitespace
"return"                                    {return RETURN;};
"var"                                       {return VAR;};
"int"                                       {yylval = new IntType(); return INTTYPE;};
"float"                                     {yylval = new FloatType(); return FLOATTYPE;};
"addr"                                      {yylval = new AddrType(); return ADDRTYPE;};
"func"                                      {yylval = new FuncType(); return FUNCTYPE;}
"type"                                      {yylval = new TypeType(); return TYPETYPE;};
"trait"                                     {return TRAIT;}
"array"                                     {return ARRAY;};
"tuple"                                     {return TUPLE;};
"cast"                                      {return CAST;};
"if"                                        {return IF;};
"else"                                      {return ELSE;};
"while"                                     {return WHILE;};
                                         
"=="                                        {return EQ;};
"<"                                         {return LT;};
">"                                         {return GT;};
"<="                                        {return LE;};
">="                                        {return GE;};
"!="                                        {return NE;};
                                         
"="                                         {return ASSIGN;};
"<-"                                        {return LASSIGN;};
"->"                                        {return RASSIGN;};
"+"                                         {return ADD;};
"-"                                         {return SUB;};
"*"                                         {return MUL;};
"/"                                         {return DIV;};
"%"                                         {return REM;};
                                         
"("                                         {return LPAREN;};
")"                                         {return RPAREN;};
"{"                                         {return LCURLY;};
"}"                                         {return RCURLY;};
"["                                         {return LBRACKET;};
"]"                                         {return RBRACKET;};
":"                                         {return COLON;};
";"                                         {return SEPARATOR;};
","                                         {return SEPARATOR;};

-?[1-9][0-9]+                               {yylval = new IntLiteral(std::stoi(yytext)); return INTLITERAL;};
-?[1-9][0-9]+.[0-9]+(e-?[1-9][0-9]+)?       {yylval = new FloatLiteral(std::stof(yytext)); return FLOATLITERAL;};
0[xX][0-9]+                                 {yylval = new AddrLiteral(std::stoul(yytext)); return ADDRLITERAL;};
[a-zA-Z_][0-9a-zA-Z_]+                      {yylval = new Identifier(yytext); return IDENTIFIER;};



%%
