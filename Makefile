DEBUG = 1

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

.PHONY: clean test fibonacci

fibonacci:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run fibonacci.cc
	$(GDB) ./run
test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run test.cc
	$(GDB) ./run
clean:
	rm -f run
