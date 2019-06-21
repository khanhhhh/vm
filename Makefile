DEBUG = 0

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

.PHONY: test



test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run source/*.c main.c
	$(GDB) ./run
clean:
	rm -f run
