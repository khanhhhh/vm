#ifndef _MEMORY_H_
#define _MEMORY_H_
#include<stdint.h>
typedef struct object_t {
	union {
		uint32_t	u32;
		int32_t		i32;
		float		f32;
		uint32_t	addr;
	};
} object;
typedef struct memory_t {
	uint32_t count;
	object *buffer;
	// registers
	uint32_t next_inst;
	uint32_t stack;
} memory;
object stack_peek(memory *mem) {
	return mem->buffer[mem->stack];
}
object stack_pop(memory *mem) {
	return mem->buffer[mem->stack++];
}
void stack_push(memory *mem, object o) {
	mem->buffer[--mem->stack] = o;
}
#endif
