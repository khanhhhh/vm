DEBUG = 2

CC = gcc
CCFLAGS = -std=c11 -fPIC -Wall -Wfatal-errors -fno-strict-aliasing
INFLAGS = -I./include
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -O3
GDB = 
endif

.PHONY: test fibonacci


fibonacci: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run source/*.c fibonacci.c
	$(GDB) ./run

hello_world: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run source/*.c helloworld.c
	$(GDB) ./run
clean:
	rm -f run
