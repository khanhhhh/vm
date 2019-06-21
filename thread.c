#include"thread.h"
static inline int32_t f2i_push(float f) {
	int *ptr = (int*)&f;
	return *ptr;
}
static inline int32_t l2i_push_first(int64_t l) {
	int32_t *ptr = (int32_t*)&l;
	return ptr[1];
}
static inline int32_t l2i_push_last(int64_t l) {
	int32_t *ptr = (int32_t*)&l;
	return ptr[0];
}
static inline int32_t d2i_push_first(double d) {
	int32_t *ptr = (int32_t*)&d;
	return ptr[1];
}
static inline int32_t d2i_push_last(double d) {
	int32_t *ptr = (int32_t*)&d;
	return ptr[0];
}

static int32_t halt(stack *s, code *c) {
	return 0;
}
static int32_t nop(stack *s, code *c) {
	return 1;
}
static int32_t aconst_null(stack *s, code *c) {
	stack_push(s, 0);
	return 1;
}
static int32_t iconst_m1(stack *s, code *c) {
	stack_push(s, -1);
	return 1;
}
static int32_t iconst_0(stack *s, code *c) {
	stack_push(s, 0);
	return 1;
}
static int32_t iconst_1(stack *s, code *c) {
	stack_push(s, 1);
	return 1;
}
static int32_t iconst_2(stack *s, code *c) {
	stack_push(s, 2);
	return 1;
}
static int32_t iconst_3(stack *s, code *c) {
	stack_push(s, 3);
	return 1;
}
static int32_t iconst_4(stack *s, code *c) {
	stack_push(s, 4);
	return 1;
}
static int32_t iconst_5(stack *s, code *c) {
	stack_push(s, 5);
	return 1;
}
static int32_t lconst_0(stack *s, code *c) {
	stack_push(s, 0x0);//l2i_push_first(0)
	stack_push(s, 0x0);//l2i_push_last(0)
	return 1;
}
static int32_t lconst_1(stack *s, code *c) {
	stack_push(s, 0x0);//l2i_push_first(1)
	stack_push(s, 0x1);//l2i_push_last(1)
	return 1;
}
static int32_t fconst_0(stack *s, code *c) {
	//f2i_push(0)
	stack_push(s, 0x00000000);
	return 1;
}
static int32_t fconst_1(stack *s, code *c) {
	//f2i_push(1)
	stack_push(s, 0x3f800000);
	return 1;
}
static int32_t fconst_2(stack *s, code *c) {
	//f2i_push(2)
	stack_push(s, 0x40000000);
	return 1;
}
static int32_t dconst_0(stack *s, code *c) {
	stack_push(s, 0);//d2i_push_first(0)
	stack_push(s, 0);//d2i_push_last(0)
	return 1;
}
static int32_t dconst_1(stack *s, code *c) {
	stack_push(s, 0x3ff00000);//d2i_push_first(1)
	stack_push(s, 0x00000000);//d2i_push_last(1)
	return 1;
}








thread thread_new(uint32_t stack_count, uint8_t *code) {
	thread t;
	t.s = stack_new(stack_count);
	t.c = code_new(code);
	for (uint8_t i=0; i<256; ++i) {
		t.ops[i] = halt;
	}
	t.ops[0x00] = nop;
	t.ops[0x01] = aconst_null;
	t.ops[0x02] = iconst_m1;
	t.ops[0x03] = iconst_0;
	t.ops[0x04] = iconst_1;
	t.ops[0x05] = iconst_2;
	t.ops[0x06] = iconst_3;
	t.ops[0x07] = iconst_4;
	t.ops[0x08] = iconst_5;
	t.ops[0x09] = lconst_0;
	t.ops[0x0a] = lconst_1;
	t.ops[0x0b] = fconst_0;
	t.ops[0x0c] = fconst_1;
	t.ops[0x0d] = fconst_2;
	t.ops[0x0e] = dconst_0;
	t.ops[0x0f] = dconst_1;
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	t.ops[0x00] = 
	t.ops[0x01] = 
	t.ops[0x02] = 
	t.ops[0x03] = 
	t.ops[0x04] = 
	t.ops[0x05] = 
	t.ops[0x06] = 
	t.ops[0x07] = 
	t.ops[0x08] = 
	t.ops[0x09] = 
	t.ops[0x0a] = 
	t.ops[0x0b] = 
	t.ops[0x0c] = 
	t.ops[0x0d] = 
	t.ops[0x0e] = 
	t.ops[0x0f] = 
	return t;
}
void thread_del(thread *t) {
	stack_del(&t->s);
	code_del(&t->c);
}
void thread_loop(thread *t) {
	while (1) {
		// FETCH CODE
		uint8_t opcode = code_fetch(&t->c, 0);
		if (t->ops[opcode] == halt) break;
		// EXECUTE
		int32_t next = t->ops[opcode](&t->s, &t->c);
		// JUMP
		code_jump(&t->c, next);
	}
}
