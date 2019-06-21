#ifndef _STACK_H_
#define _STACK_H_
#include"object.h"
typedef struct stack_t {
	uint32_t sp; // sp-1 : top of the stack
	uint32_t fp; // fp : bottom of the frame, usually points to return value
	object *mem; //
	uint32_t last_frame; // frame_addr[last_frame]: previous fp
	uint32_t *frame_addr;
} stack;
// CONSTRUCTOR
stack	stack_new(uint32_t count, uint32_t frame_count);
// DESTRUCTOR
void	stack_del(stack *s);
// STACK OP
object	stack_peek(stack *s);
object	stack_pop(stack *s);
void	stack_push(stack *s, object item);
void	stack_frame_call(stack *s, uint32_t num_args);
void	stack_frame_return(stack *s);
object	stack_frame_load(stack *s, uint32_t offset);
void	stack_frame_store(stack *s, uint32_t offset, object item);
#endif
