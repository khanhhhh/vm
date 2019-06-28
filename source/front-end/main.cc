#include<parser.tab.h>
int yyparse();
Program* Program::program;
std::vector<Expr*> Expr::all_expr;
int main() {
	FILE *f = fopen("code.boo", "r");
	yyin = f;
	do {
		yyparse();
	} while(!feof(yyin));
	fclose(f);
	return 0;
}
