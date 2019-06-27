compile: clean gen
	g++ -I./ -fPIC -g -o run lex.yy.c parser.tab.c main.cc
gen:
	bison -d -v parser.y
	flex lexer.l
clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h parser.output
