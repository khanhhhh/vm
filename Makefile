DEBUG = 0

CC = clang++
CCFLAGS = -std=c++17 -fPIC -Wall -Wfatal-errors -march=native -Wl,-O1
INFLAGS = -I./include
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -Ofast
GDB = 
endif

.PHONY: clean fibonacci_recur

fibonacci:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run test/fibonacci/fibonacci.cc
	$(GDB) ./run
clean:
	rm -f run
