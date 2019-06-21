#ifndef _STACK_H_
#define _STACK_H_
#include<stdint.h>
typedef int32_t object;
typedef struct stack_t {
	uint32_t top;
	object *mem;
} stack;
// CONSTRUCTOR
stack	stack_new(uint32_t count);
// DESTRUCTOR
void	stack_del(stack *s);
// STACK OP
object	stack_peek(stack *s);
object	stack_pop(stack *s);
void	stack_push(stack *s, object item);
#endif
