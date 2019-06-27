compile: gen
	g++ -I./ -fPIC -shared -o libparser.so *.c
gen:
	bison -d -v parser.y
	flex lexer.l
