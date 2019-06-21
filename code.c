#include"code.h"
code	code_new(uint8_t *mem) {
	code c;
	c.pos = 0;
	c.mem = mem;
	return c;
}
void	code_del() {}
uint8_t	code_fetch(code *c, uint32_t offset) {
	return c->mem[c->pos + offset];
}
void	code_jump(code *c, uint32_t offset) {
	c->pos += offset;
}
