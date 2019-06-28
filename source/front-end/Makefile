DEBUG = 1

CC = g++
CCFLAGS = -fPIC -Wall -Wfatal-errors

INFLAGS = -I./
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -O3
GDB = 
endif

.PHONY: clean test parser lexer 

test: clean all
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run main.cc ./libparser.so
all: parser lexer
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -c -o parser.tab.o parser.tab.c
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -c -o lex.yy.o lex.yy.c
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -shared -o libparser.so *.o
parser:
	bison -d -v parser.y
lexer:
	flex lexer.l
clean:
	rm -f *.yy.c *.output *.tab.* *.o

