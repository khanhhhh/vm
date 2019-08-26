DEBUG = 0

CC = g++
CCFLAGS = -std=c++17 -fPIC -Wall -Wfatal-errors -march=native
INFLAGS = -I./include
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -O3
GDB = 
endif

.PHONY: clean fibonacci_recur

fibonacci:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) test/fibonacci/fibonacci.cc
	$(GDB) ./a.out
clean:
	rm -f *.out *.s *.ll
