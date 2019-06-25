%{
#include"parser.tab.h"
#include"AST.hh"
%}



%%
"return"                                    {yylval.string = yytext; return(RETURN);}
"var"                                       {yylval.string = yytext; return(VAR);}
"int"                                       {yylval.string = yytext; return(INT);}
"float"                                     {yylval.string = yytext; return(FLOAT);}
"addr"                                      {yylval.string = yytext; return(ADDR);}
"array"                                     {yylval.string = yytext; return(ARRAY);}
"tuple"                                     {yylval.string = yytext; return(TUPLE);}
"type"                                      {yylval.string = yytext; return(TYPE);}
"cast"                                      {yylval.string = yytext; return(CAST);}
"if"                                        {yylval.string = yytext; return(IF);}
"else"                                      {yylval.string = yytext; return(ELSE);}
"while"                                     {yylval.string = yytext; return(WHILE);}
                                         
"=="                                        {yylval.string = yytext; return(EQ);}
"<"                                         {yylval.string = yytext; return(LT);}
">"                                         {yylval.string = yytext; return(GT);}
"<="                                        {yylval.string = yytext; return(LE);}
">="                                        {yylval.string = yytext; return(GE);}
"!="                                        {yylval.string = yytext; return(NE);}
                                         
"="                                         {yylval.string = yytext; return(ASSIGN);}
"<-"                                        {yylval.string = yytext; return(LASSIGN);}
"->"                                        {yylval.string = yytext; return(RASSIGN);}
"+"                                         {yylval.string = yytext; return(ADD);}
"-"                                         {yylval.string = yytext; return(SUB);}
"*"                                         {yylval.string = yytext; return(MUL);}
"/"                                         {yylval.string = yytext; return(DIV);}
"%"                                         {yylval.string = yytext; return(REM);}
                                         
"("                                         {yylval.string = yytext; return(LPAREN);}
")"                                         {yylval.string = yytext; return(RPAREN);}
"{"                                         {yylval.string = yytext; return(LCURLY);}
"}"                                         {yylval.string = yytext; return(LCURLY);}
"["                                         {yylval.string = yytext; return(LBRACKET);}
"]"                                         {yylval.string = yytext; return(RBRACKET);}
":"                                         {yylval.string = yytext; return(COLON);}
";"                                         {yylval.string = yytext; return(SEPARATOR);}
","                                         {yylval.string = yytext; return(SEPARATOR);}

-?[1-9][0-9]+                               {yylval.string = yytext; return(INTLITERAL, yytext);}
-?[1-9][0-9]+.[0-9]+(e-?[1-9][0-9]+)?       {yylval.string = yytext; return(FLOATLITERAL, yytext);}
0[xX][0-9]+                                 {yylval.string = yytext; return(ADDRLITERAL, yytext);}
[a-zA-Z_][0-9a-zA-Z_]+                      {yylval.string = yytext; return(IDENTIFIER, yytext);}
<<EOF>>                                     {yylval.string = yytext; return(EOF, yytext);}


%%
int yywrap(){return 1;}
