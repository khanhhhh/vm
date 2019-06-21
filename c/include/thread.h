#ifndef _THREAD_H_
#define _THREAD_H_
#include"stack.h"
#include"code.h"
#include"data.h"
typedef int32_t (*instruction)(stack *s, code *c, data *d);
typedef struct thread_t {
	instruction ops[256];
	stack s;
	code c;
	data d;
} thread;
// CONSTRUCTOR
thread	thread_new(uint8_t *code, object *data);
// DESTRUCTOR
void	thread_del(thread *t);
// EXECUTION
void	thread_loop(thread *t);
#endif
