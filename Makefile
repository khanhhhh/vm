DEBUG = 1

CC = gcc
CCFLAGS = -std=c11 -fPIC -Wall -Wfatal-errors
INFLAGS = -I.
LDFLAGS = 

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
else
CCFLAGS += -DNDEBUG -O3
endif

test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./test.c
clean:
	rm -f run
