compile: gen
	g++ -I./ -fPIC -o run lex.yy.c parser.tab.c main.cc
gen:
	bison -d -v parser.y
	flex lexer.l
