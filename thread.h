#ifndef _THREAD_H_
#define _THREAD_H_
#include"code.h"
#include"stack.h"
typedef int32_t (*instruction)(stack *s, code *c);
typedef struct thread_t {
	instruction ops[256];
	code c;
	stack s;
} thread;
// CONSTRUCTOR
thread	thread_new(uint32_t stack_count, uint8_t *code);
// DESTRUCTOR
void	thread_del(thread *t);
// EXECUTION
void	thread_loop(thread *t);
#endif
