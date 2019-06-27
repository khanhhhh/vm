

%code requires {
#include<ast.hh>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
}
%{
%}


%token NUMBER
%token ADD

%type<integer> NUMBER
%type<string> ADD
%type<node> Sum

%%
Sum[obj]:
    NUMBER[num] {
    $obj = new Number($num);
}
|   Sum[left] ADD NUMBER[right] {
    $obj = new Sum($left, new Number($right));
};
%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

