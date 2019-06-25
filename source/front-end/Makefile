
DEBUG = 0

CC = g++
CCFLAGS = -std=c++17 -fPIC -Wall -Wfatal-errors -march=native 
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

test: all
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run main.cc
	$(GDB) ./run
all: parser lexer
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -shared -o libparser.so lex.yy.c parser.tab.c
parser:
	bison -d -v parser.y
lexer:
	flex lexer.l
clean:
	rm -f *.yy.c *.output *.tab.*

