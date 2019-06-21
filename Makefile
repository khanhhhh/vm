DEBUG = 0

CC = gcc
CCFLAGS = -std=c11 -fPIC -Wall -Wfatal-errors
INFLAGS = -I.
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
GDB = gdb
else
CCFLAGS += -DNDEBUG -O3
GDB = 
endif





test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run *.c
	$(GDB) ./run
clean:
	rm -f run
