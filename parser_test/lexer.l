%option noyywrap
%{
#include<parser.tab.h>
#include<stdio.h>
#define YY_DECL int yylex()
%}
%%
"+"             {yylval.string = std::string(yytext); return ADD;};
[1-9][0-9]*     {yylval.integer = std::stoi(yytext); return NUMBER;};
%%