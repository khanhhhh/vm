DEBUG = 0

CC = g++
CCFLAGS = -std=c++17 -fPIC -Wall -Wfatal-errors 
INFLAGS = -I./include
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -O3
GDB = 
endif

.PHONY: clean test fibonacci fibonacci_iter

test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run test.cc
	$(GDB) ./run
fibonacci_iter:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run test/fibonacci/fibonacci_iter.cc
	$(GDB) ./run
fibonacci_recur:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run test/fibonacci/fibonacci_recur.cc
	$(GDB) ./run
clean:
	rm -f run
