all: parser lexer

parser:
	bison -d -v parser.y
lexer:
	flex lexer.l
clean:
	rm -f *.yy.c *.output *.tab.*
