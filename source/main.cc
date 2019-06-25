#include"lex.yy.c"
#include<cstdio>
int main(int argc, char **argv) {
	if (argc >= 2) {
		yyin = fopen(argv[1], "r");
		yylex();
	}
	return 0;
}
