#include<parser.tab.h>
Program* Program::program;
int main() {
	FILE *f = fopen("code.boo", "r");
	yyin = f;
	do {
		yyparse();
	} while(!feof(yyin));
	fclose(f);
	return 0;
}