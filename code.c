#include"code.h"
code	code_new(uint8_t *mem) {
	code c;
	c.pos = 0;
	c.mem = mem;
	return c;
}
void	code_del() {}

uint8_t	 code_fetch(code *c) {
	return c->mem[c->pos];
}
uint32_t code_fetch_param(code *c) {
	uint32_t *out = (uint32_t*)(c->mem + c->pos + 1);
	return *out;
}
void	code_jump(code *c, uint32_t offset) {
	c->pos += offset;
}
