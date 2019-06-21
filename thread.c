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
	t.ops[0x10] = 
	t.ops[0x11] = 
	t.ops[0x12] = 
	t.ops[0x13] = 
	t.ops[0x14] = 
	t.ops[0x15] = 
	t.ops[0x16] = 
	t.ops[0x17] = 
	t.ops[0x18] = 
	t.ops[0x19] = 
	t.ops[0x1a] = 
	t.ops[0x1b] = 
	t.ops[0x1c] = 
	t.ops[0x1d] = 
	t.ops[0x1e] = 
	t.ops[0x1f] = 
	t.ops[0x20] = 
	t.ops[0x21] = 
	t.ops[0x22] = 
	t.ops[0x23] = 
	t.ops[0x24] = 
	t.ops[0x25] = 
	t.ops[0x26] = 
	t.ops[0x27] = 
	t.ops[0x28] = 
	t.ops[0x29] = 
	t.ops[0x2a] = 
	t.ops[0x2b] = 
	t.ops[0x2c] = 
	t.ops[0x2d] = 
	t.ops[0x2e] = 
	t.ops[0x2f] = 
	t.ops[0x30] = 
	t.ops[0x31] = 
	t.ops[0x32] = 
	t.ops[0x33] = 
	t.ops[0x34] = 
	t.ops[0x35] = 
	t.ops[0x36] = 
	t.ops[0x37] = 
	t.ops[0x38] = 
	t.ops[0x39] = 
	t.ops[0x3a] = 
	t.ops[0x3b] = 
	t.ops[0x3c] = 
	t.ops[0x3d] = 
	t.ops[0x3e] = 
	t.ops[0x3f] = 
	t.ops[0x40] = 
	t.ops[0x41] = 
	t.ops[0x42] = 
	t.ops[0x43] = 
	t.ops[0x44] = 
	t.ops[0x45] = 
	t.ops[0x46] = 
	t.ops[0x47] = 
	t.ops[0x48] = 
	t.ops[0x49] = 
	t.ops[0x4a] = 
	t.ops[0x4b] = 
	t.ops[0x4c] = 
	t.ops[0x4d] = 
	t.ops[0x4e] = 
	t.ops[0x4f] = 
	t.ops[0x50] = 
	t.ops[0x51] = 
	t.ops[0x52] = 
	t.ops[0x53] = 
	t.ops[0x54] = 
	t.ops[0x55] = 
	t.ops[0x56] = 
	t.ops[0x57] = 
	t.ops[0x58] = 
	t.ops[0x59] = 
	t.ops[0x5a] = 
	t.ops[0x5b] = 
	t.ops[0x5c] = 
	t.ops[0x5d] = 
	t.ops[0x5e] = 
	t.ops[0x5f] = 
	t.ops[0x60] = 
	t.ops[0x61] = 
	t.ops[0x62] = 
	t.ops[0x63] = 
	t.ops[0x64] = 
	t.ops[0x65] = 
	t.ops[0x66] = 
	t.ops[0x67] = 
	t.ops[0x68] = 
	t.ops[0x69] = 
	t.ops[0x6a] = 
	t.ops[0x6b] = 
	t.ops[0x6c] = 
	t.ops[0x6d] = 
	t.ops[0x6e] = 
	t.ops[0x6f] = 
	t.ops[0x70] = 
	t.ops[0x71] = 
	t.ops[0x72] = 
	t.ops[0x73] = 
	t.ops[0x74] = 
	t.ops[0x75] = 
	t.ops[0x76] = 
	t.ops[0x77] = 
	t.ops[0x78] = 
	t.ops[0x79] = 
	t.ops[0x7a] = 
	t.ops[0x7b] = 
	t.ops[0x7c] = 
	t.ops[0x7d] = 
	t.ops[0x7e] = 
	t.ops[0x7f] = 
	t.ops[0x80] = 
	t.ops[0x81] = 
	t.ops[0x82] = 
	t.ops[0x83] = 
	t.ops[0x84] = 
	t.ops[0x85] = 
	t.ops[0x86] = 
	t.ops[0x87] = 
	t.ops[0x88] = 
	t.ops[0x89] = 
	t.ops[0x8a] = 
	t.ops[0x8b] = 
	t.ops[0x8c] = 
	t.ops[0x8d] = 
	t.ops[0x8e] = 
	t.ops[0x8f] = 
	t.ops[0x90] = 
	t.ops[0x91] = 
	t.ops[0x92] = 
	t.ops[0x93] = 
	t.ops[0x94] = 
	t.ops[0x95] = 
	t.ops[0x96] = 
	t.ops[0x97] = 
	t.ops[0x98] = 
	t.ops[0x99] = 
	t.ops[0x9a] = 
	t.ops[0x9b] = 
	t.ops[0x9c] = 
	t.ops[0x9d] = 
	t.ops[0x9e] = 
	t.ops[0x9f] = 
	t.ops[0xa0] = 
	t.ops[0xa1] = 
	t.ops[0xa2] = 
	t.ops[0xa3] = 
	t.ops[0xa4] = 
	t.ops[0xa5] = 
	t.ops[0xa6] = 
	t.ops[0xa7] = 
	t.ops[0xa8] = 
	t.ops[0xa9] = 
	t.ops[0xaa] = 
	t.ops[0xab] = 
	t.ops[0xac] = 
	t.ops[0xad] = 
	t.ops[0xae] = 
	t.ops[0xaf] = 
	t.ops[0xb0] = 
	t.ops[0xb1] = 
	t.ops[0xb2] = 
	t.ops[0xb3] = 
	t.ops[0xb4] = 
	t.ops[0xb5] = 
	t.ops[0xb6] = 
	t.ops[0xb7] = 
	t.ops[0xb8] = 
	t.ops[0xb9] = 
	t.ops[0xba] = 
	t.ops[0xbb] = 
	t.ops[0xbc] = 
	t.ops[0xbd] = 
	t.ops[0xbe] = 
	t.ops[0xbf] = 
	t.ops[0xc0] = 
	t.ops[0xc1] = 
	t.ops[0xc2] = 
	t.ops[0xc3] = 
	t.ops[0xc4] = 
	t.ops[0xc5] = 
	t.ops[0xc6] = 
	t.ops[0xc7] = 
	t.ops[0xc8] = 
	t.ops[0xc9] = 
	t.ops[0xca] = 
	t.ops[0xcb] = 
	t.ops[0xcc] = 
	t.ops[0xcd] = 
	t.ops[0xce] = 
	t.ops[0xcf] = 
	t.ops[0xd0] = 
	t.ops[0xd1] = 
	t.ops[0xd2] = 
	t.ops[0xd3] = 
	t.ops[0xd4] = 
	t.ops[0xd5] = 
	t.ops[0xd6] = 
	t.ops[0xd7] = 
	t.ops[0xd8] = 
	t.ops[0xd9] = 
	t.ops[0xda] = 
	t.ops[0xdb] = 
	t.ops[0xdc] = 
	t.ops[0xdd] = 
	t.ops[0xde] = 
	t.ops[0xdf] = 
	t.ops[0xe0] = 
	t.ops[0xe1] = 
	t.ops[0xe2] = 
	t.ops[0xe3] = 
	t.ops[0xe4] = 
	t.ops[0xe5] = 
	t.ops[0xe6] = 
	t.ops[0xe7] = 
	t.ops[0xe8] = 
	t.ops[0xe9] = 
	t.ops[0xea] = 
	t.ops[0xeb] = 
	t.ops[0xec] = 
	t.ops[0xed] = 
	t.ops[0xee] = 
	t.ops[0xef] = 
	t.ops[0xf0] = 
	t.ops[0xf1] = 
	t.ops[0xf2] = 
	t.ops[0xf3] = 
	t.ops[0xf4] = 
	t.ops[0xf5] = 
	t.ops[0xf6] = 
	t.ops[0xf7] = 
	t.ops[0xf8] = 
	t.ops[0xf9] = 
	t.ops[0xfa] = 
	t.ops[0xfb] = 
	t.ops[0xfc] = 
	t.ops[0xfd] = 
	t.ops[0xfe] = 
	t.ops[0xff] = 
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
