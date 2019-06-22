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
inline	void	jump(stype offset) {
		ip += offset;
	}
inline	stype	ip_offset(utype dst) {
		return dst - ip;
	}
	// STACK MANIPULATION
inline	utype*	stack_ptr() {
		return &stack[sp];
	}
inline	utype	stack_peek() {
		return stack[sp - 1];
	}
inline	utype	stack_pop() {
		sp--;
		shv--;
		return stack[sp];
	}
inline	void	stack_push(utype item) {
		stack[sp] = item;
		sp++;
		shv++;
	}
inline	void	stack_advance(stype len) {
		sp += len;
		shv += len;
	}
inline	utype	stack_load(utype offset) {
		return stack[fp + offset];
	}
inline	void	stack_memmove(utype dst, utype src, utype len) {
		std::memmove(stack + dst, stack + src, len * sizeof(utype));	
	}
inline	void	stack_store(utype offset, utype item) {
		stack[fp + offset] = item;
	}
inline	// STACK CALLING FUNCTION
	void	stack_push_fp() {
		sp++;			// placeholder for return address
		stack_push(fp);		// store frame pointer
		shv = 0;		// set shv to zero to calculate hm arguments
	}
inline	void	stack_call() {
		fp = sp - shv;		// set frame pointer to the first argument
		stack[fp - 2] = ip;	// set return address to ip
	}
inline	utype	stack_return() {
		sp = fp - 2;		// restore stack pointer
		fp = stack[sp + 1];	// restore frame pointer
		return stack[sp];	// return address;
	}
public:
	thread(const i_code<opcode, utype>& c, i_data<utype>& d, utype stack_count = 1024):
		i_thread<opcode, utype>(c, d),
		ip(1),	// code starts at ip = 1 (code[0] = halt)
		sp(2),	// program starts at sp = 2. (stack[0]: return addr = 0, halt, stack[1] = 0)
		fp(0),
		shv(0),
		stack((utype*)std::malloc(stack_count * sizeof(utype)))
       	{
		stack_store(0, 0);
		stack_store(1, 0);
		ops[0x00] = &thread::halt;
		ops[0x01] = &thread::nop;
		ops[0x02] = &thread::load_code;
		ops[0x03] = &thread::load_code_array;
		ops[0x04] = &thread::load_data;
		ops[0x05] = &thread::load_data_array;
		ops[0x06] = &thread::load_stack;
		ops[0x07] = &thread::load_stack_array;
		ops[0x08] = &thread::store_data;
		ops[0x09] = &thread::store_data_array;
		ops[0x0a] = &thread::store_stack;
		ops[0x0b] = &thread::store_stack_array;
		ops[0x0c] = &thread::pop;
		ops[0x0d] = &thread::dup;
		ops[0x0e] = &thread::swap;
		ops[0x0f] = &thread::iadd;
		ops[0x10] = &thread::fadd;
		ops[0x11] = &thread::isub;
		ops[0x12] = &thread::fsub;
		ops[0x13] = &thread::imul;
		ops[0x14] = &thread::fmul;
		ops[0x15] = &thread::idiv;
		ops[0x16] = &thread::fdiv;
		ops[0x17] = &thread::irem;
		ops[0x18] = &thread::ineg;
		ops[0x19] = &thread::fneg;
		ops[0x1a] = &thread::i2f;
		ops[0x1b] = &thread::f2i;
		ops[0x1c] = &thread::jump;
		ops[0x1d] = &thread::ifeq_jump;
		ops[0x1e] = &thread::iflt_jump;
		ops[0x1f] = &thread::ifgt_jump;
		ops[0x20] = &thread::ifle_jump;
		ops[0x21] = &thread::ifge_jump;
		ops[0x22] = &thread::ifne_jump;
		ops[0x23] = &thread::push_fp;
		ops[0x24] = &thread::call_fp;
		ops[0x25] = &thread::return0;
		ops[0x26] = &thread::return1;
		ops[0x27] = &thread::return1_array;
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
		// halt should not be called!
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
	// LOADCODE + PARAM
	stype load_code() {
		utype param = c.fetch_param(ip + 1);
		stack_push(param);
		return 1 + 4;
	}
	// LOADCODEARRAY + LEN + {ARRAY}
	stype load_code_array() {
		utype len = c.fetch_param(ip + 1);
		c.fetch_array(ip + 1 + 4, len, stack_ptr());
		stack_advance((stype)len);
		return 1 + 4 + 4*len;
	}
	// LOADDATA + BASE
	stype load_data() {
		utype base = c.fetch_param(ip + 1);
		stack_push(d.load(base));
		return 1 + 4;
	}
	// LOADDATAARRAY + LEN + BASE
	stype load_data_array() {
		utype len = c.fetch_param(ip + 1);
		utype base = c.fetch_param(ip + 1 + 4);
		d.load_array(base, len, stack_ptr());
		stack_advance((stype)len);
		return 1 + 4 + 4;
	}
	// LOADSTACK + BASE
	stype load_stack() {
		utype addr = c.fetch_param(ip + 1);
		utype out = stack_load(addr);
		stack_push(out);
		return 1 + 4;
	}
	// LOADSTACKARRAY + LEN + BASE
	stype load_stack_array() {
		utype len = c.fetch_param(ip + 1);
		utype base = c.fetch_param(ip + 1 + 4);
		stack_memmove(sp, base, len);
		stack_advance((stype)len);
		return 1 + 4 + 4;
	}
	// STORE DATA
	// STOREDATA + BASE
	stype store_data() {
		utype base = c.fetch_param(ip + 1);
		d.store(base, stack_pop());
		return 1 + 4;
	}
	// STOREDATAARRAY + LEN + BASE
	stype store_data_array() {
		utype len = c.fetch_param(ip + 1);
		utype base = c.fetch_param(ip + 1 + 4);
		d.store_array(base, len, stack_ptr() - len);
		stack_advance(- (stype)len);
		return 1 + 4 + 4;
	}
	// STORESTACK + BASE 
	stype store_stack() {
		utype base = c.fetch_param(ip + 1);
		stack_store(base, stack_pop());
		return 1 + 4;
	}
	// STORESTACKARRAY + LEN + BASE
	stype store_stack_array() {
		utype len = c.fetch_param(ip + 1);
		utype base = c.fetch_param(ip + 1 + 4);
		stack_memmove(base, sp - len, len);
		stack_advance(- (stype)len);
		return 1 + 4 + 4;
	}
	// STACK MANIPULATION
	// POP
	stype pop() {
		stack_pop();
		return 1;
	}
	// DUP
	stype dup() {
		stack_push(stack_peek());
		return 1;
	}
	// SWAP
	stype swap() {
		utype out1 = stack_pop();
		utype out2 = stack_pop();
		stack_push(out1);
		stack_push(out2);
		return 1;
	}
	// ARITHMETIC
	// helpers
		static inline stype _u2s(utype in) {
			return (stype)in;
		}
		static inline utype _s2u(stype in) {
			return (utype)in;
		}
		static inline ftype _u2f(utype in) {
			ftype *out = (ftype*)&in;
			return *out;
		}
		static inline utype _f2u(ftype in) {
			utype *out = (utype*)&in;
			return *out;
		}
	// IADD
	stype iadd() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a + b));
		return 1;
	}
	// FADD
	stype fadd() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a + b));
		return 1;
	}
	// ISUB
	stype isub() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a - b));
		return 1;
	}
	// FSUB
	stype fsub() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a - b));
		return 1;
	}
	// IMUL
	stype imul() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a * b));
		return 1;
	}
	// FMUL
	stype fmul() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a * b));
		return 1;
	}
	// IDIV
	stype idiv() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a / b));
		return 1;
	}
	// FDIV
	stype fdiv() {
		ftype b = _u2f(stack_pop());
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(a / b));
		return 1;
	}
	// IREM
	stype irem() {
		stype b = _u2s(stack_pop());
		stype a = _u2s(stack_pop());
		stack_push(_s2u(a % b));
		return 1;
	}
	// INEG
	stype ineg() {
		stype a = _u2s(stack_pop());
		stack_push(_s2u(- a));
		return 1;
	}
	// FNEG
	stype fneg() {
		ftype a = _u2f(stack_pop());
		stack_push(_f2u(- a));
		return 1;
	}
// TYPE CONVERSION
	// I2F
	stype i2f() {
		stype a = _u2s(stack_pop());
		stack_push(_f2u((ftype)a));
		return 1;
	}
	// F2I
	stype f2i() {
		ftype a = _u2f(stack_pop());
		stack_push(_s2u((stype)a));
		return 1;
	}
// JUMP
	// JUMP DST
	stype jump() {
		stype dst = _u2s(c.fetch_param(ip + 1));
		return ip_offset(dst);
	}
// CONDITIONAL JUMP
	// IFEQ_JUMP DST
	stype ifeq_jump() {
		stype cond = _u2s(stack_pop());
		if (cond == 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	// IFLT_JUMP DST
	stype iflt_jump() {
		stype cond = _u2s(stack_pop());
		if (cond < 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	// IFGT_JUMP DST
	stype ifgt_jump() {
		stype cond = _u2s(stack_pop());
		if (cond > 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	// IFLE_JUMP DST
	stype ifle_jump() {
		stype cond = _u2s(stack_pop());
		if (cond <= 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	// IFGE_JUMP DST
	stype ifge_jump() {
		stype cond = _u2s(stack_pop());
		if (cond >= 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
	// IFNE_JUMP DST
	stype ifne_jump() {
		stype cond = _u2s(stack_pop());
		if (cond != 0) {
			stype dst = _u2s(c.fetch_param(ip + 1));
			return ip_offset(dst);
		}
		return 1 + 4;
	}
// FUNCTION CALL = PUSH_FP -> PREPARE STACK -> CALL_FP
	// PUSH_FP
	stype push_fp() {
		stack_push_fp();
		return 1;
	}
	// CALL_FP
	stype call_fp() {
		stack_call();
		stype dst = _u2s(c.fetch_param(ip + 1));
		return ip_offset(dst);
	}
	// RETURN0
	stype return0() {
		utype dst = stack_return();
		return ip_offset(dst) + 5;
	}
	// RETURN1
	stype return1() {
		utype out = stack_pop();
		utype dst = stack_return();
		stack_push(out);
		return ip_offset(dst) + 5;
	}
	// RETURN1ARRAY LEN
	stype return1_array() {
		utype len = c.fetch_param(ip + 1);
		utype *arr = (utype*)std::malloc(len * sizeof(utype));
		std::memcpy(arr, stack_ptr() - len, len * sizeof(utype));
		stack_advance(- (stype)len);
		utype dst = stack_return();
		std::memcpy(stack_ptr(), arr, len * sizeof(utype));
		return ip_offset(dst) + 5;
	}
};
#endif
