#include<parser.tab.h>
std::vector<Node*> Node::all_nodes;
int main() {
	FILE *f = fopen("code.boo", "r");
	yyin = f;
	do {
		yyparse();
	} while(!feof(yyin));
	fclose(f);
	return 0;
}