#include"stack.h"
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
	s->sh = 0;
	stack_push(s, s->fp);
}

void	stack_call(stack *s) {
	s->fp = s->sp - s->sh;
}
void	stack_return(stack *s) {
	s->sp = s->fp - 1;
	s->fp = s->mem[s->fp - 1];
}
object	stack_load(stack *s, uint32_t offset) {
	return s->mem[s->fp + offset];
}
void	stack_store(stack *s, uint32_t offset, object item) {
	s->mem[s->fp + offset] = item;
}

