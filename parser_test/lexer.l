%option noyywrap
%{
#include<parser.tab.h>
#include<cstdio>
#define YY_DECL int yylex()
%}
%%
"+"             {
                    std::printf("yytext: %s\n", yytext);
                    //yylval.string = std::string(yytext);
                    return ADD;
                };
[1-9][0-9]*     {yylval.integer = std::stoi(yytext); return NUMBER;};
%%