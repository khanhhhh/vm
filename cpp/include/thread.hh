#ifndef _THREAD_HH_
#define _THREAD_HH_
#include"i_thread.hh"
#include"code.hh"
#include"data.hh"
#include<cstdint>
#include<cstdlib>
#include<cstdio>
//template<class opcode, class utype>

using opcode	= uint8_t;
using utype	= uint32_t;
using stype	= int32_t;
using ftype	= float;
using program	= code<opcode, utype>;
using heap	= data<utype>;


class thread: public i_thread<opcode, utype> {
private:
	utype ip; // instruction pointer: current instruction index
	utype sp; // stack pointer: stack[sp-1] is top of the stack
	utype fp; // frame pointer: fucntion call convention 
	utype shv; // stack height variation: used for function call
	utype *stack;
	typedef stype (thread::* instruction)();
	instruction ops[256];
	// JUMP
	void	jump(stype offset) {
		ip += offset;
	}
	stype	ip_offset(utype dst) {
		return dst - ip;
	}
	// STACK MANIPULATION
	utype	stack_peek() {
		return stack[sp - 1];
	}
	utype	stack_pop() {
		sp--;
		shv--;
		return stack[sp];
	}
	void	stack_push(utype item) {
		stack[sp] = item;
		sp++;
		shv++;
	}
	utype	stack_load(utype offset) {
		return stack[fp + offset];
	}
	void	stack_store(utype offset, utype item) {
		stack[fp + offset] = item;
	}
	// STACK CALLING FUNCTION
	void	stack_push_fp() {
		sp++;			// placeholder for return address
		stack_push(fp);		// store frame pointer
		shv = 0;		// set shv to zero to calculate hm arguments
	}
	void	stack_call() {
		fp = sp - shv;		// set frame pointer to the first argument
		stack[fp - 2] = ip;	// set return address to ip
	}
	utype	stack_return() {
		sp = fp - 2;		// restore stack pointer
		fp = stack[sp + 1];	// restore frame pointer
		return stack[sp];	// return address;
	}
public:
	thread(const i_code<opcode, utype>& c, i_data<utype>& d, utype stack_count = 1024):
		i_thread<opcode, utype>(c, d),
		ip(0),
		sp(0),
		fp(0),
		shv(0),
		stack((utype*)std::malloc(stack_count * sizeof(utype)))
       	{
		ops[0x00] = &thread::nop;
		ops[0x01] = &thread::load_code;
		ops[0x02] = &thread::load_data;
		ops[0x03] = &thread::load_stack;
		ops[0x04] = &thread::store_data;
		ops[0x05] = &thread::store_stack;
		ops[0x06] = &thread::pop;
		ops[0x07] = &thread::dup;
		ops[0x08] = &thread::swap;
		ops[0x09] = &thread::iadd;
		ops[0x0a] = &thread::fadd;
		ops[0x0b] = &thread::isub;
		ops[0x0c] = &thread::fsub;
		ops[0x0d] = &thread::imul;
		ops[0x0e] = &thread::fmul;
		ops[0x0f] = &thread::idiv;
		ops[0x10] = &thread::fdiv;
		ops[0x11] = &thread::irem;
		ops[0x12] = &thread::ineg;
		ops[0x13] = &thread::fneg;
		ops[0x14] = &thread::i2f;
		ops[0x15] = &thread::f2i;
		ops[0x16] = &thread::jump;
		ops[0x17] = &thread::ifeq_jump;
		ops[0x18] = &thread::iflt_jump;
		ops[0x19] = &thread::ifgt_jump;
		ops[0x1a] = &thread::ifle_jump;
		ops[0x1b] = &thread::ifge_jump;
		ops[0x1c] = &thread::ifne_jump;
		ops[0x1d] = &thread::push_fp;
		ops[0x1e] = &thread::call_fp;
		ops[0x1f] = &thread::return0;
		ops[0x20] = &thread::return1;
		ops[0x21] = &thread::halt;
		ops[0x22] = &thread::halt;
		ops[0x23] = &thread::halt;
		ops[0x24] = &thread::halt;
		ops[0x25] = &thread::halt;
		ops[0x26] = &thread::halt;
		ops[0x27] = &thread::halt;
		ops[0x28] = &thread::halt;
		ops[0x29] = &thread::halt;
		ops[0x2a] = &thread::halt;
		ops[0x2b] = &thread::halt;
		ops[0x2c] = &thread::halt;
		ops[0x2d] = &thread::halt;
		ops[0x2e] = &thread::halt;
		ops[0x2f] = &thread::halt;
		ops[0x30] = &thread::halt;
		ops[0x31] = &thread::halt;
		ops[0x32] = &thread::halt;
		ops[0x33] = &thread::halt;
		ops[0x34] = &thread::halt;
		ops[0x35] = &thread::halt;
		ops[0x36] = &thread::halt;
		ops[0x37] = &thread::halt;
		ops[0x38] = &thread::halt;
		ops[0x39] = &thread::halt;
		ops[0x3a] = &thread::halt;
		ops[0x3b] = &thread::halt;
		ops[0x3c] = &thread::halt;
		ops[0x3d] = &thread::halt;
		ops[0x3e] = &thread::halt;
		ops[0x3f] = &thread::halt;
		ops[0x40] = &thread::halt;
		ops[0x41] = &thread::halt;
		ops[0x42] = &thread::halt;
		ops[0x43] = &thread::halt;
		ops[0x44] = &thread::halt;
		ops[0x45] = &thread::halt;
		ops[0x46] = &thread::halt;
		ops[0x47] = &thread::halt;
		ops[0x48] = &thread::halt;
		ops[0x49] = &thread::halt;
		ops[0x4a] = &thread::halt;
		ops[0x4b] = &thread::halt;
		ops[0x4c] = &thread::halt;
		ops[0x4d] = &thread::halt;
		ops[0x4e] = &thread::halt;
		ops[0x4f] = &thread::halt;
		ops[0x50] = &thread::halt;
		ops[0x51] = &thread::halt;
		ops[0x52] = &thread::halt;
		ops[0x53] = &thread::halt;
		ops[0x54] = &thread::halt;
		ops[0x55] = &thread::halt;
		ops[0x56] = &thread::halt;
		ops[0x57] = &thread::halt;
		ops[0x58] = &thread::halt;
		ops[0x59] = &thread::halt;
		ops[0x5a] = &thread::halt;
		ops[0x5b] = &thread::halt;
		ops[0x5c] = &thread::halt;
		ops[0x5d] = &thread::halt;
		ops[0x5e] = &thread::halt;
		ops[0x5f] = &thread::halt;
		ops[0x60] = &thread::halt;
		ops[0x61] = &thread::halt;
		ops[0x62] = &thread::halt;
		ops[0x63] = &thread::halt;
		ops[0x64] = &thread::halt;
		ops[0x65] = &thread::halt;
		ops[0x66] = &thread::halt;
		ops[0x67] = &thread::halt;
		ops[0x68] = &thread::halt;
		ops[0x69] = &thread::halt;
		ops[0x6a] = &thread::halt;
		ops[0x6b] = &thread::halt;
		ops[0x6c] = &thread::halt;
		ops[0x6d] = &thread::halt;
		ops[0x6e] = &thread::halt;
		ops[0x6f] = &thread::halt;
		ops[0x70] = &thread::halt;
		ops[0x71] = &thread::halt;
		ops[0x72] = &thread::halt;
		ops[0x73] = &thread::halt;
		ops[0x74] = &thread::halt;
		ops[0x75] = &thread::halt;
		ops[0x76] = &thread::halt;
		ops[0x77] = &thread::halt;
		ops[0x78] = &thread::halt;
		ops[0x79] = &thread::halt;
		ops[0x7a] = &thread::halt;
		ops[0x7b] = &thread::halt;
		ops[0x7c] = &thread::halt;
		ops[0x7d] = &thread::halt;
		ops[0x7e] = &thread::halt;
		ops[0x7f] = &thread::halt;
		ops[0x80] = &thread::halt;
		ops[0x81] = &thread::halt;
		ops[0x82] = &thread::halt;
		ops[0x83] = &thread::halt;
		ops[0x84] = &thread::halt;
		ops[0x85] = &thread::halt;
		ops[0x86] = &thread::halt;
		ops[0x87] = &thread::halt;
		ops[0x88] = &thread::halt;
		ops[0x89] = &thread::halt;
		ops[0x8a] = &thread::halt;
		ops[0x8b] = &thread::halt;
		ops[0x8c] = &thread::halt;
		ops[0x8d] = &thread::halt;
		ops[0x8e] = &thread::halt;
		ops[0x8f] = &thread::halt;
		ops[0x90] = &thread::halt;
		ops[0x91] = &thread::halt;
		ops[0x92] = &thread::halt;
		ops[0x93] = &thread::halt;
		ops[0x94] = &thread::halt;
		ops[0x95] = &thread::halt;
		ops[0x96] = &thread::halt;
		ops[0x97] = &thread::halt;
		ops[0x98] = &thread::halt;
		ops[0x99] = &thread::halt;
		ops[0x9a] = &thread::halt;
		ops[0x9b] = &thread::halt;
		ops[0x9c] = &thread::halt;
		ops[0x9d] = &thread::halt;
		ops[0x9e] = &thread::halt;
		ops[0x9f] = &thread::halt;
		ops[0xa0] = &thread::halt;
		ops[0xa1] = &thread::halt;
		ops[0xa2] = &thread::halt;
		ops[0xa3] = &thread::halt;
		ops[0xa4] = &thread::halt;
		ops[0xa5] = &thread::halt;
		ops[0xa6] = &thread::halt;
		ops[0xa7] = &thread::halt;
		ops[0xa8] = &thread::halt;
		ops[0xa9] = &thread::halt;
		ops[0xaa] = &thread::halt;
		ops[0xab] = &thread::halt;
		ops[0xac] = &thread::halt;
		ops[0xad] = &thread::halt;
		ops[0xae] = &thread::halt;
		ops[0xaf] = &thread::halt;
		ops[0xb0] = &thread::halt;
		ops[0xb1] = &thread::halt;
		ops[0xb2] = &thread::halt;
		ops[0xb3] = &thread::halt;
		ops[0xb4] = &thread::halt;
		ops[0xb5] = &thread::halt;
		ops[0xb6] = &thread::halt;
		ops[0xb7] = &thread::halt;
		ops[0xb8] = &thread::halt;
		ops[0xb9] = &thread::halt;
		ops[0xba] = &thread::halt;
		ops[0xbb] = &thread::halt;
		ops[0xbc] = &thread::halt;
		ops[0xbd] = &thread::halt;
		ops[0xbe] = &thread::halt;
		ops[0xbf] = &thread::halt;
		ops[0xc0] = &thread::halt;
		ops[0xc1] = &thread::halt;
		ops[0xc2] = &thread::halt;
		ops[0xc3] = &thread::halt;
		ops[0xc4] = &thread::halt;
		ops[0xc5] = &thread::halt;
		ops[0xc6] = &thread::halt;
		ops[0xc7] = &thread::halt;
		ops[0xc8] = &thread::halt;
		ops[0xc9] = &thread::halt;
		ops[0xca] = &thread::halt;
		ops[0xcb] = &thread::halt;
		ops[0xcc] = &thread::halt;
		ops[0xcd] = &thread::halt;
		ops[0xce] = &thread::halt;
		ops[0xcf] = &thread::halt;
		ops[0xd0] = &thread::halt;
		ops[0xd1] = &thread::halt;
		ops[0xd2] = &thread::halt;
		ops[0xd3] = &thread::halt;
		ops[0xd4] = &thread::halt;
		ops[0xd5] = &thread::halt;
		ops[0xd6] = &thread::halt;
		ops[0xd7] = &thread::halt;
		ops[0xd8] = &thread::halt;
		ops[0xd9] = &thread::halt;
		ops[0xda] = &thread::halt;
		ops[0xdb] = &thread::halt;
		ops[0xdc] = &thread::halt;
		ops[0xdd] = &thread::halt;
		ops[0xde] = &thread::halt;
		ops[0xdf] = &thread::halt;
		ops[0xe0] = &thread::halt;
		ops[0xe1] = &thread::halt;
		ops[0xe2] = &thread::halt;
		ops[0xe3] = &thread::halt;
		ops[0xe4] = &thread::halt;
		ops[0xe5] = &thread::halt;
		ops[0xe6] = &thread::halt;
		ops[0xe7] = &thread::halt;
		ops[0xe8] = &thread::halt;
		ops[0xe9] = &thread::halt;
		ops[0xea] = &thread::halt;
		ops[0xeb] = &thread::halt;
		ops[0xec] = &thread::halt;
		ops[0xed] = &thread::halt;
		ops[0xee] = &thread::halt;
		ops[0xef] = &thread::halt;
		ops[0xf0] = &thread::halt;
		ops[0xf1] = &thread::halt;
		ops[0xf2] = &thread::halt;
		ops[0xf3] = &thread::halt;
		ops[0xf4] = &thread::halt;
		ops[0xf5] = &thread::halt;
		ops[0xf6] = &thread::halt;
		ops[0xf7] = &thread::halt;
		ops[0xf8] = &thread::halt;
		ops[0xf9] = &thread::halt;
		ops[0xfa] = &thread::halt;
		ops[0xfb] = &thread::halt;
		ops[0xfc] = &thread::print_int;
		ops[0xfd] = &thread::print_float;
		ops[0xfe] = &thread::print_char;
		ops[0xff] = &thread::halt;
	}
	~thread() {
		std::free(stack);
	}
	bool iterate() {
		// FETCH
		opcode op_name = c.fetch(ip);
		// DECODE
		auto op_func = this->ops[op_name];
		if (op_func == &thread::halt)
			return false;
		// EXECUTE
		jump((this->*op_func)());
		return true;
	}
private:
	// INSTRUCTIONS
	// instruction return relative address to jump
	stype halt() {
		return 0;
	}
	stype nop() {
		return 1;
	}
	stype print_char() {
		utype out = stack_peek();
		char cout = (char)out;
		std::putchar(cout);
		return 1;
	}
	stype print_int() {
		std::printf("%d", _u2s(stack_peek()));
		return 1;
	}
	stype print_float() {
		std::printf("%f", _u2f(stack_peek()));
		return 1;
	}
	// LOAD DATA
	stype load_code() {
		utype param = c.fetch_param(ip + 1);
		stack_push(param);
		return 1 + 4;
	}
	stype load_data() {
		utype addr = c.fetch_param(ip + 1);
		utype out = d.load(addr);
		stack_push(out);
		return 1 + 4;
	}
	stype load_stack() {
		utype addr = c.fetch_param(ip + 1);
		utype out = stack_load(addr);
		stack_push(out);
		return 1 + 4;
	}
	// STORE DATA
	stype store_data() {
		utype addr = c.fetch_param(ip + 1);
		utype out = stack_pop();
		d.store(addr, out);
		return 1 + 4;
	}
	stype store_stack() {
		utype addr = c.fetch_param(ip + 1);
		utype out = stack_pop();
		stack_store(addr,  out);
		return 1 + 4;
	}
	// STACK MANIPULATION
	stype pop() {
		stack_pop();
		return 1;
	}
	stype dup() {
		utype out = stack_peek();
		stack_push(out);
		return 1;
	}
	stype swap() {
		utype out1 = stack_pop();
		utype out2 = stack_pop();
		stack_push(out1);
		stack_push(out2);
		return 1;
	}
	// ARITHMETIC
	// helpers
		inline stype _u2s(utype in) {
			return (stype)in;
		}
		inline utype _s2u(stype in) {
			return (utype)in;
		}
		inline ftype _u2f(utype in) {
			ftype *out = (ftype*)&in;
			return *out;
		}
		inline utype _f2u(ftype in) {
			utype *out = (utype*)&in;
			return *out;
		}
	stype iadd() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a + b));
		return 1;
	}
	stype fadd() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a + b));
		return 1;
	}
	stype isub() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a - b));
		return 1;
	}
	stype fsub() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a - b));
		return 1;
	}
	stype imul() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a * b));
		return 1;
	}
	stype fmul() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a * b));
		return 1;
	}
	stype idiv() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a / b));
		return 1;
	}
	stype fdiv() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a / b));
		return 1;
	}
	stype irem() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a % b));
		return 1;
	}
	stype ineg() {
		stype a = _u2s(stack_pop());
		stack_push(_s2u(- a));
		return 1;
	}
	stype fneg() {
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(- a));
		return 1;
	}
// TYPE CONVERSION
	stype i2f() {
		stype a = _u2s(stack_pop());
		stack_push(_f2u((ftype)a));
		return 1;
	}
	stype f2i() {
		ftype a = _u2f(stack_pop());
		stack_push(_s2u((stype)a));
		return 1;
	}
// JUMP
	stype jump() {
		stype dst = _u2s(c.fetch_param(ip + 1));
		return ip_offset(dst);
	}
// CONDITIONAL JUMP
	stype ifeq_jump() {
		stype cond = _u2s(stack_pop());
		if (cond == 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	stype iflt_jump() {
		stype cond = _u2s(stack_pop());
		if (cond < 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	stype ifgt_jump() {
		stype cond = _u2s(stack_pop());
		if (cond > 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	stype ifle_jump() {
		stype cond = _u2s(stack_pop());
		if (cond <= 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	stype ifge_jump() {
		stype cond = _u2s(stack_pop());
		if (cond >= 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	stype ifne_jump() {
		stype cond = _u2s(stack_pop());
		if (cond != 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
// FUNCTION CALL = PUSH_FP -> PREPARE STACK -> CALL_FP
	stype push_fp() {
		stack_push_fp();
		return 1;
	}
	stype call_fp() {
		stack_call();
		stype dst = _u2s(c.fetch_param(ip + 1));
		return ip_offset(dst);
	}
	stype return0() {
		utype dst = stack_return();
		return ip_offset(dst) + 5;
	}
	stype return1() {
		utype out = stack_pop();
		utype dst = stack_return();
		stack_push(out);
		return ip_offset(dst) + 5;
	}
};
#endif
