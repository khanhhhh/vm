

%code requires {
#include<ast.hh>
#include<string>
#include<cstring>
typedef union somename{
    Node *node;
    int integer;
    std::string string;
    somename() {}
    somename(const somename& obj) {
        std::memcpy(this, &obj, sizeof(somename));
    }
    somename& operator=(const somename& obj) {
        std::memcpy(this, &obj, sizeof(somename));
        return *this;
    }
    ~somename() {};
} YYSTYPE;
}
%{
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
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

int main() {
	yyin = stdin;
	do {
		yyparse();
	} while(!feof(yyin));
	return 0;
}
void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

