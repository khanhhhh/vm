#include<parser.tab.h>
int yyparse();
Program* Program::program;
int main() {
	FILE *f = fopen("code.boo", "r");
	yyin = f;
	do {
		yyparse();
		std::printf("parsing...\n");
	} while(!feof(yyin));
	fclose(f);
	return 0;
}
