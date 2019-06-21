#include"stack.h"
#include<stdlib.h>
stack	stack_new(uint32_t count) {
	stack s;
	s.sp = 0;
	s.fp = 0;
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
	return s->mem[--s->sp];
}
void	stack_push(stack *s, object item) {
	s->mem[s->sp++] = item;
}

void	stack_frame_call(stack *s) {
	stack_push(s, s->fp);
	s->fp = s->sp;
}
void	stack_frame_return(stack *s) {
	s->sp = s->fp - 1;
	s->fp = s->mem[s->fp - 1];
}
object	stack_frame_load(stack *s, uint32_t offset) {
	return s->mem[s->fp + offset];
}
void	stack_frame_store(stack *s, uint32_t offset, object item) {
	s->mem[s->fp + offset] = item;
}

