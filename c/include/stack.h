#ifndef _STACK_H_
#define _STACK_H_
#include"object.h"
typedef struct stack_t {
	uint32_t sp; // sp-1 : top of the stack
	uint32_t fp; // fp : bottom of the frame, usually points to return value
	uint32_t sh;
	object *mem; //
} stack;
// CONSTRUCTOR
stack	stack_new(uint32_t count);
// DESTRUCTOR
void	stack_del(stack *s);
// STACK OP
object	stack_peek(stack *s);
object	stack_pop(stack *s);
void	stack_push(stack *s, object item);
//function call procedure:
//0. stack_push_fp : push return address and frame pointer
//2. push parameters
//1. stack_frame_call : set fp sp to new value
//3. jump / execute code
//4. stack_frame_return : get return value and reset
// fp = stack_pop() + stack_pop()
void	stack_push_fp(stack *s);
void	stack_call(stack *s, uint32_t ret_addr);
uint32_t stack_return(stack *s);
object	stack_load(stack *s, uint32_t offset);
void	stack_store(stack *s, uint32_t offset, object item);
void	stack_print(stack *s);
#endif