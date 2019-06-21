#include"thread.h"
#include<stdio.h>
static int32_t halt(stack *s, code *c, data *d) {
	return 0;
}
static int32_t nop(stack *s, code *c, data *d) {
	return 1;
}
static int32_t load_code(stack *s, code *c, data *d) {
	object in = (object)code_fetch_param(c);
	stack_push(s, in);
	return 1 + 4;
}
static int32_t load_data(stack *s, code *c, data *d) {
	uint32_t offset = (uint32_t)code_fetch_param(c);
	object in = data_load(d, offset);
	stack_push(s, in);
	return 1 + 4;
}
static int32_t load_stack(stack *s, code *c, data *d) {
	uint32_t offset = (uint32_t)code_fetch_param(c);
	object in = stack_frame_load(s, offset);
	stack_push(s, in);
	return 1 + 4;
}
static int32_t store_data(stack *s, code *c, data *d) {
	uint32_t offset = (uint32_t)code_fetch_param;
	object in = stack_pop(s);
	data_store(d, offset, in);
	return 1 + 4;
}
static int32_t store_stack(stack *s, code *c, data *d) {
	uint32_t offset = (uint32_t)code_fetch_param(c);
	object in = stack_pop(s);
	stack_frame_store(s, offset, in);
	return 1 + 4;
}
static int32_t pop(stack *s, code *c, data *d) {
	stack_pop(s);
	return 1;
}
static int32_t dup(stack *s, code *c, data *d) {
	object in = stack_pop(s);
	stack_push(s, in);
	stack_push(s, in);
	return 1;
}
static int32_t swap(stack *s, code *c, data *d) {
	object in1 = stack_pop(s);
	object in2 = stack_pop(s);
	stack_push(s, in1);
	stack_push(s, in2);
	return 1;
}

static int32_t iadd(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	int32_t out = in2 + in1;
	stack_push(s, out);
	return 1;
}
static int32_t fadd(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	
	float fin1 = *((float*)&in1);
	float fin2 = *((float*)&in2);
	float fout = fin2 + fin1;

	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t isub(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	int32_t out = in2 - in1;
	stack_push(s, out);
	return 1;
}
static int32_t fsub(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	
	float fin1 = *((float*)&in1);
	float fin2 = *((float*)&in2);
	float fout = fin2 - fin1;

	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t imul(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	int32_t out = in2 * in1;
	stack_push(s, out);
	return 1;
}
static int32_t fmul(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	
	float fin1 = *((float*)&in1);
	float fin2 = *((float*)&in2);
	float fout = fin2 * fin1;

	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t idiv(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	int32_t out = in2 / in1;
	stack_push(s, out);
	return 1;
}
static int32_t fdiv(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	
	float fin1 = *((float*)&in1);
	float fin2 = *((float*)&in2);
	float fout = fin2 / fin1;

	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t irem(stack *s, code *c, data *d) {
	int32_t in1 = (int32_t)stack_pop(s);
	int32_t in2 = (int32_t)stack_pop(s);
	int32_t out = in2 % in1;
	stack_push(s, out);
	return 1;
}
static int32_t ineg(stack *s, code *c, data *d) {
	int32_t in = (int32_t)stack_pop(s);
	int32_t out = -in;
	stack_push(s, out);
	return 1;
}
static int32_t fneg(stack *s, code *c, data *d) {
	int32_t in = (int32_t)stack_pop(s);

	float fin = *((float*)&in);
	float fout = -fin;

	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t i2f(stack *s, code *c, data *d) {
	int32_t in = (int32_t)stack_pop(s);
	float fout = (float)in;
	int32_t out = *((int32_t*)(&fout));
	stack_push(s, out);
	return 1;
}
static int32_t f2i(stack *s, code *c, data *d) {
	int32_t in = (int32_t)stack_pop(s);

	float fin = *((float*)&in);

	int32_t out = (int32_t)fin;
	stack_push(s, out);
	return 1;
}






thread thread_new(uint8_t *code, object *data) {
	thread t;
	t.s = stack_new(1024, 256);
	t.c = code_new(code);
	t.d = data_new(data);
	for (uint8_t i=0; i<256; ++i) {
		t.ops[i] = halt;
	}
	t.ops[0x00] = nop;
	t.ops[0x01] = halt;
	t.ops[0x02] = halt;
	t.ops[0x03] = halt;
	t.ops[0x04] = halt;
	t.ops[0x05] = halt;
	t.ops[0x06] = halt;
	t.ops[0x07] = halt;
	t.ops[0x08] = halt;
	t.ops[0x09] = halt;
	t.ops[0x0a] = halt;
	t.ops[0x0b] = halt;
	t.ops[0x0c] = halt;
	t.ops[0x0d] = halt;
	t.ops[0x0e] = halt;
	t.ops[0x0f] = halt;
	t.ops[0x10] = halt;
	t.ops[0x11] = halt;
	t.ops[0x12] = halt;
	t.ops[0x13] = halt;
	t.ops[0x14] = halt;
	t.ops[0x15] = halt;
	t.ops[0x16] = halt;
	t.ops[0x17] = halt;
	t.ops[0x18] = halt;
	t.ops[0x19] = halt;
	t.ops[0x1a] = halt;
	t.ops[0x1b] = halt;
	t.ops[0x1c] = halt;
	t.ops[0x1d] = halt;
	t.ops[0x1e] = halt;
	t.ops[0x1f] = halt;
	t.ops[0x20] = halt;
	t.ops[0x21] = halt;
	t.ops[0x22] = halt;
	t.ops[0x23] = halt;
	t.ops[0x24] = halt;
	t.ops[0x25] = halt;
	t.ops[0x26] = halt;
	t.ops[0x27] = halt;
	t.ops[0x28] = halt;
	t.ops[0x29] = halt;
	t.ops[0x2a] = halt;
	t.ops[0x2b] = halt;
	t.ops[0x2c] = halt;
	t.ops[0x2d] = halt;
	t.ops[0x2e] = halt;
	t.ops[0x2f] = halt;
	t.ops[0x30] = halt;
	t.ops[0x31] = halt;
	t.ops[0x32] = halt;
	t.ops[0x33] = halt;
	t.ops[0x34] = halt;
	t.ops[0x35] = halt;
	t.ops[0x36] = halt;
	t.ops[0x37] = halt;
	t.ops[0x38] = halt;
	t.ops[0x39] = halt;
	t.ops[0x3a] = halt;
	t.ops[0x3b] = halt;
	t.ops[0x3c] = halt;
	t.ops[0x3d] = halt;
	t.ops[0x3e] = halt;
	t.ops[0x3f] = halt;
	t.ops[0x40] = halt;
	t.ops[0x41] = halt;
	t.ops[0x42] = halt;
	t.ops[0x43] = halt;
	t.ops[0x44] = halt;
	t.ops[0x45] = halt;
	t.ops[0x46] = halt;
	t.ops[0x47] = halt;
	t.ops[0x48] = halt;
	t.ops[0x49] = halt;
	t.ops[0x4a] = halt;
	t.ops[0x4b] = halt;
	t.ops[0x4c] = halt;
	t.ops[0x4d] = halt;
	t.ops[0x4e] = halt;
	t.ops[0x4f] = halt;
	t.ops[0x50] = halt;
	t.ops[0x51] = halt;
	t.ops[0x52] = halt;
	t.ops[0x53] = halt;
	t.ops[0x54] = halt;
	t.ops[0x55] = halt;
	t.ops[0x56] = halt;
	t.ops[0x57] = halt;
	t.ops[0x58] = halt;
	t.ops[0x59] = halt;
	t.ops[0x5a] = halt;
	t.ops[0x5b] = halt;
	t.ops[0x5c] = halt;
	t.ops[0x5d] = halt;
	t.ops[0x5e] = halt;
	t.ops[0x5f] = halt;
	t.ops[0x60] = halt;
	t.ops[0x61] = halt;
	t.ops[0x62] = halt;
	t.ops[0x63] = halt;
	t.ops[0x64] = halt;
	t.ops[0x65] = halt;
	t.ops[0x66] = halt;
	t.ops[0x67] = halt;
	t.ops[0x68] = halt;
	t.ops[0x69] = halt;
	t.ops[0x6a] = halt;
	t.ops[0x6b] = halt;
	t.ops[0x6c] = halt;
	t.ops[0x6d] = halt;
	t.ops[0x6e] = halt;
	t.ops[0x6f] = halt;
	t.ops[0x70] = halt;
	t.ops[0x71] = halt;
	t.ops[0x72] = halt;
	t.ops[0x73] = halt;
	t.ops[0x74] = halt;
	t.ops[0x75] = halt;
	t.ops[0x76] = halt;
	t.ops[0x77] = halt;
	t.ops[0x78] = halt;
	t.ops[0x79] = halt;
	t.ops[0x7a] = halt;
	t.ops[0x7b] = halt;
	t.ops[0x7c] = halt;
	t.ops[0x7d] = halt;
	t.ops[0x7e] = halt;
	t.ops[0x7f] = halt;
	t.ops[0x80] = halt;
	t.ops[0x81] = halt;
	t.ops[0x82] = halt;
	t.ops[0x83] = halt;
	t.ops[0x84] = halt;
	t.ops[0x85] = halt;
	t.ops[0x86] = halt;
	t.ops[0x87] = halt;
	t.ops[0x88] = halt;
	t.ops[0x89] = halt;
	t.ops[0x8a] = halt;
	t.ops[0x8b] = halt;
	t.ops[0x8c] = halt;
	t.ops[0x8d] = halt;
	t.ops[0x8e] = halt;
	t.ops[0x8f] = halt;
	t.ops[0x90] = halt;
	t.ops[0x91] = halt;
	t.ops[0x92] = halt;
	t.ops[0x93] = halt;
	t.ops[0x94] = halt;
	t.ops[0x95] = halt;
	t.ops[0x96] = halt;
	t.ops[0x97] = halt;
	t.ops[0x98] = halt;
	t.ops[0x99] = halt;
	t.ops[0x9a] = halt;
	t.ops[0x9b] = halt;
	t.ops[0x9c] = halt;
	t.ops[0x9d] = halt;
	t.ops[0x9e] = halt;
	t.ops[0x9f] = halt;
	t.ops[0xa0] = halt;
	t.ops[0xa1] = halt;
	t.ops[0xa2] = halt;
	t.ops[0xa3] = halt;
	t.ops[0xa4] = halt;
	t.ops[0xa5] = halt;
	t.ops[0xa6] = halt;
	t.ops[0xa7] = halt;
	t.ops[0xa8] = halt;
	t.ops[0xa9] = halt;
	t.ops[0xaa] = halt;
	t.ops[0xab] = halt;
	t.ops[0xac] = halt;
	t.ops[0xad] = halt;
	t.ops[0xae] = halt;
	t.ops[0xaf] = halt;
	t.ops[0xb0] = halt;
	t.ops[0xb1] = halt;
	t.ops[0xb2] = halt;
	t.ops[0xb3] = halt;
	t.ops[0xb4] = halt;
	t.ops[0xb5] = halt;
	t.ops[0xb6] = halt;
	t.ops[0xb7] = halt;
	t.ops[0xb8] = halt;
	t.ops[0xb9] = halt;
	t.ops[0xba] = halt;
	t.ops[0xbb] = halt;
	t.ops[0xbc] = halt;
	t.ops[0xbd] = halt;
	t.ops[0xbe] = halt;
	t.ops[0xbf] = halt;
	t.ops[0xc0] = halt;
	t.ops[0xc1] = halt;
	t.ops[0xc2] = halt;
	t.ops[0xc3] = halt;
	t.ops[0xc4] = halt;
	t.ops[0xc5] = halt;
	t.ops[0xc6] = halt;
	t.ops[0xc7] = halt;
	t.ops[0xc8] = halt;
	t.ops[0xc9] = halt;
	t.ops[0xca] = halt;
	t.ops[0xcb] = halt;
	t.ops[0xcc] = halt;
	t.ops[0xcd] = halt;
	t.ops[0xce] = halt;
	t.ops[0xcf] = halt;
	t.ops[0xd0] = halt;
	t.ops[0xd1] = halt;
	t.ops[0xd2] = halt;
	t.ops[0xd3] = halt;
	t.ops[0xd4] = halt;
	t.ops[0xd5] = halt;
	t.ops[0xd6] = halt;
	t.ops[0xd7] = halt;
	t.ops[0xd8] = halt;
	t.ops[0xd9] = halt;
	t.ops[0xda] = halt;
	t.ops[0xdb] = halt;
	t.ops[0xdc] = halt;
	t.ops[0xdd] = halt;
	t.ops[0xde] = halt;
	t.ops[0xdf] = halt;
	t.ops[0xe0] = halt;
	t.ops[0xe1] = halt;
	t.ops[0xe2] = halt;
	t.ops[0xe3] = halt;
	t.ops[0xe4] = halt;
	t.ops[0xe5] = halt;
	t.ops[0xe6] = halt;
	t.ops[0xe7] = halt;
	t.ops[0xe8] = halt;
	t.ops[0xe9] = halt;
	t.ops[0xea] = halt;
	t.ops[0xeb] = halt;
	t.ops[0xec] = halt;
	t.ops[0xed] = halt;
	t.ops[0xee] = halt;
	t.ops[0xef] = halt;
	t.ops[0xf0] = halt;
	t.ops[0xf1] = halt;
	t.ops[0xf2] = halt;
	t.ops[0xf3] = halt;
	t.ops[0xf4] = halt;
	t.ops[0xf5] = halt;
	t.ops[0xf6] = halt;
	t.ops[0xf7] = halt;
	t.ops[0xf8] = halt;
	t.ops[0xf9] = halt;
	t.ops[0xfa] = halt;
	t.ops[0xfb] = halt;
	t.ops[0xfc] = halt;
	t.ops[0xfd] = halt;
	t.ops[0xfe] = halt;
	t.ops[0xff] = halt;
	return t;
}
void thread_del(thread *t) {
	stack_del(&t->s);
	code_del(&t->c);
	data_del(&t->d);
}
void thread_loop(thread *t) {
	while (1) {
		// FETCH CODE
		uint8_t opcode = code_fetch(&t->c);
		if (t->ops[opcode] == halt) break;
		// EXECUTE
		int32_t next = t->ops[opcode](&t->s, &t->c, &t->d);
		// JUMP
		code_jump(&t->c, next);
	}
}
