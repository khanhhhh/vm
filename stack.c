#include"stack.h"
#include<stdlib.h>
stack	stack_new(uint32_t count, uint32_t frame_count) {
	stack s;
	s.sp = 0;
	s.fp = 0;
	s.mem = (object*)malloc(count*sizeof(object));
	s.last_frame = 0;
	s.frame_addr = (uint32_t*)malloc(frame_count*sizeof(uint32_t));
	s.frame_addr[0] = 0;
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


void	stack_frame_call(stack *s, uint32_t num_args) {
	s->last_frame++;
	s->frame_addr[s->last_frame] = s->fp;
	s->fp = s->sp - num_args;
}
void	stack_frame_return(stack *s) {
	s->sp = s->fp;
	s->fp = s->frame_addr[s->last_frame--];
}
object	stack_frame_load(stack *s, uint32_t offset) {
	return s->mem[s->fp + offset];
}
void	stack_frame_store(stack *s, uint32_t offset, object item) {
	s->mem[s->fp + offset] = item;
}

