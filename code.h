#ifndef _CODE_H_
#define _CODE_H_
#include<stdint.h>
typedef struct code_t {
	uint32_t pos;
	uint8_t *mem;
} code;
// CONSTRUCTOR
code	code_new(uint8_t *mem);
// DESTRUCTOR
void	code_del();
// FETCH CODE
uint8_t	code_fetch(code *c, uint32_t offset);
// JUMP
void	code_jump(code *c, uint32_t offset);
#endif
