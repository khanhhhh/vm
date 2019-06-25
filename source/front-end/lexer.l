%{
#include"parser.tab.h"
%}



%%
"return"                                    {yylval.lexeme = yytext; return(RETURN);}
"var"                                       {yylval.lexeme = yytext; return(VAR);}
"int"                                       {yylval.lexeme = yytext; return(INT);}
"float"                                     {yylval.lexeme = yytext; return(FLOAT);}
"addr"                                      {yylval.lexeme = yytext; return(ADDR);}
"array"                                     {yylval.lexeme = yytext; return(ARRAY);}
"tuple"                                     {yylval.lexeme = yytext; return(TUPLE);}
"type"                                      {yylval.lexeme = yytext; return(TYPE);}
"cast"                                      {yylval.lexeme = yytext; return(CAST);}
"if"                                        {yylval.lexeme = yytext; return(IF);}
"else"                                      {yylval.lexeme = yytext; return(ELSE);}
"while"                                     {yylval.lexeme = yytext; return(WHILE);}
                                         
"=="                                        {yylval.lexeme = yytext; return(EQ);}
"<"                                         {yylval.lexeme = yytext; return(LT);}
">"                                         {yylval.lexeme = yytext; return(GT);}
"<="                                        {yylval.lexeme = yytext; return(LE);}
">="                                        {yylval.lexeme = yytext; return(GE);}
"!="                                        {yylval.lexeme = yytext; return(NE);}
                                         
"="                                         {yylval.lexeme = yytext; return(ASSIGN);}
"<-"                                        {yylval.lexeme = yytext; return(LASSIGN);}
"->"                                        {yylval.lexeme = yytext; return(RASSIGN);}
"+"                                         {yylval.lexeme = yytext; return(ADD);}
"-"                                         {yylval.lexeme = yytext; return(SUB);}
"*"                                         {yylval.lexeme = yytext; return(MUL);}
"/"                                         {yylval.lexeme = yytext; return(DIV);}
"%"                                         {yylval.lexeme = yytext; return(REM);}
                                         
"("                                         {yylval.lexeme = yytext; return(LPAREN);}
")"                                         {yylval.lexeme = yytext; return(RPAREN);}
"{"                                         {yylval.lexeme = yytext; return(LCURLY);}
"}"                                         {yylval.lexeme = yytext; return(LCURLY);}
"["                                         {yylval.lexeme = yytext; return(LBRACKET);}
"]"                                         {yylval.lexeme = yytext; return(RBRACKET);}
":"                                         {yylval.lexeme = yytext; return(COLON);}
";"                                         {yylval.lexeme = yytext; return(SEPARATOR);}
","                                         {yylval.lexeme = yytext; return(SEPARATOR);}

-?[1-9][0-9]+                               {yylval.lexeme = yytext; return(INTLITERAL, yytext);}
-?[1-9][0-9]+.[0-9]+(e-?[1-9][0-9]+)?       {yylval.lexeme = yytext; return(FLOATLITERAL, yytext);}
0[xX][0-9]+                                 {yylval.lexeme = yytext; return(ADDRLITERAL, yytext);}
[a-zA-Z_][0-9a-zA-Z_]+                      {yylval.lexeme = yytext; return(IDENTIFIER, yytext);}
<<EOF>>                                     {yylval.lexeme = yytext; return(EOF, yytext);}


%%
int yywrap(){return 1;}
