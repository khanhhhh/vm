#include"stack.h"
#include<stdio.h>
#include<stdlib.h>
stack	stack_new(uint32_t count) {
	stack s;
	s.sp = 0;
	s.fp = 0;
	s.sh = 0;
	s.mem = (object*)malloc(count*sizeof(object));
	return s;
}
void	stack_del(stack *s) {
	free(s->mem);
}
object	stack_peek(stack *s) {
	return s->mem[s->sp - 1];
}
object	stack_pop(stack *s) {
	s->sh--;
	s->sp--;
	return s->mem[s->sp];
}
void	stack_push(stack *s, object item) {
	s->sh++;
	s->mem[s->sp] = item;
	s->sp++;
}
void	stack_push_fp(stack *s) {
	stack_push(s, 0);	// return addr
	stack_push(s, s->fp);	// frame pointer
	s->sh = 0;
}

void	stack_call(stack *s, uint32_t ret_addr) {
	s->fp = s->sp - s->sh;	// set frame pointer
	s->mem[s->fp - 2] = ret_addr;
}
uint32_t stack_return(stack *s) {
	s->sp = s->fp - 2;	// set stack pointer back (2 = return addr + old fp)
	s->fp = s->mem[s->fp - 1];	// set frame pointer back
	return s->mem[s->sp];
}
object	stack_load(stack *s, uint32_t offset) {
	return s->mem[s->fp + offset];
}
void	stack_store(stack *s, uint32_t offset, object item) {
	s->mem[s->fp + offset] = item;
}

void	stack_print(stack *s) {
	printf("----- STACK -----\n");
	printf("\tsh: %u\n", s->sh);
	printf("\t[");
		for (int i=s->fp; i<s->sp ; i++) {
			printf("%d, ", s->mem[i]);
		}
	printf("]\n");
}
