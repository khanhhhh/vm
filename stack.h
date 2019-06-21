#ifndef _STACK_H_
#define _STACK_H_
#include"object.h"
typedef struct stack_t {
	uint32_t sp; // sp-1 : top of the stack
	uint32_t fp; // fp : bottom of the frame, usually points to return value
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
//1. stack_frame_call
//2. push_parameters
//3. jump / execute code
//4. stack_frame_return
// fp = stack_pop() + stack_pop()
void	stack_frame_call(stack *s); // push fp value on top of the stack. set fp to next value. later prepare the function call parameter by stack_push
void	stack_frame_return(stack *s); //
object	stack_frame_load(stack *s, uint32_t offset);
void	stack_frame_store(stack *s, uint32_t offset, object item);
#endif
