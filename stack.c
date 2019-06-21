#include"stack.h"
#include<stdlib.h>
stack	stack_new(uint32_t count) {
	stack s;
	s.top = 0;
	s.mem = (object*)malloc(count*sizeof(object));
	return s;
}
void	stack_del(stack *s) {
	free(s->mem);
}
object	stack_peek(stack *s) {
	return s->mem[s->top - 1];
}
object	stack_pop(stack *s) {
	return s->mem[--s->top];
}
void	stack_push(stack *s, object item) {
	s->mem[s->top++] = item;
}

