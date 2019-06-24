#ifndef _THREAD_HH_
#define _THREAD_HH_
#include"i_thread.hh"
#include"code.hh"
#include"data.hh"
#include<cstdint>
#include<cstdlib>
#include<cstdio>
#include<array>

// constants
using opcode = uint8_t;
using utype	= uint32_t;
using stype	= int32_t;
using ftype	= float;
const int count	= 1024;
// class name
template<uint32_t count> using program = code<opcode, utype, count>;
template<uint32_t count> using heap = data<utype, count>;

class thread: public i_thread<opcode, utype> {
public:
	typedef stype (thread::* instruction)();
	static std::array<instruction, 256> ops;
private:
	utype ip; // instruction pointer: current instruction index
	utype sp; // stack pointer: stack[sp-1] is top of the stack
	utype fp; // frame pointer: fucntion call convention 
	utype shv; // stack height variation: used for function call
	std::array<utype, count> stack;
private:
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
		std::memmove(stack.data() + dst, stack.data() + src, len * sizeof(utype));	
	}
	inline	void	stack_store(utype offset, utype item) {
		stack[fp + offset] = item;
	}
	void	stack_print() {
		std::printf("[");
		for (utype i = fp; i < sp; i++)
			std::printf("%u, ", stack[i]);
		std::printf("]\n");
	}
	// STACK CALLING FUNCTION
	inline	void	stack_push_fp() {
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
		ip(0),
		sp(0),	
		fp(0),
		shv(0),
		stack()
       	{
	}
	~thread() {}
	bool iterate() {
			//stack_print();
		// FETCH
		opcode op_name = c.fetch(ip);
			//std::printf("ip: %u, opcode: 0x%x\n", ip, op_name);
		// DECODE
		auto op_func = this->ops[op_name];
		if (op_func == &thread::halt)
			return false;
		// EXECUTE
		jump((this->*op_func)());
		return true;
	}
public:
	// INSTRUCTIONS
	// instruction return relative address to jump
	stype halt() {
		// halt should not be called!
		return 0;
	}
	stype nop() {
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
	// PUSH
	stype push() {
		stack_advance(+1);
		return 1;
	}
	// PUSHARRAY LEN
	stype push_array() {
		utype len = c.fetch_param(ip + 1);
		stack_advance(+ (stype)len);
		return 1 + 4;
	}
	// POP
	stype pop() {
		stack_advance(-1);
		return 1;
	}
	// POPARRAY LEN
	stype pop_array() {
		utype len = c.fetch_param(ip + 1);
		stack_advance(- (stype)len);
		return 1 + 4;
	}
	// DUP
	stype dup() {
		stack_push(stack_peek());
		return 1;
	}
	// DUPARRAY LEN
	stype dup_array() {
		utype len = c.fetch_param(ip + 1);
		stack_memmove(sp, sp - len, len);
		stack_advance(+ (stype)len);
		return 1 + 4;
	}
	// SWAP
	stype swap() {
		utype out1 = stack_pop();
		utype out2 = stack_pop();
		stack_push(out1);
		stack_push(out2);
		return 1;
	}
	// SWAPARRAY LEN
	stype swap_array() {
		utype len = c.fetch_param(ip + 1);
		utype *arr = (utype*)std::malloc(len * sizeof(utype));
		std::memcpy(arr, stack_ptr() - len, len * sizeof(utype));
		std::memcpy(stack_ptr() - len, stack_ptr() - 2*len, len * sizeof(utype));
		std::memcpy(stack_ptr() - 2*len, arr, len * sizeof(utype));
		std::free(arr);
		return 1 + 4;
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
		std::free(arr);
		return ip_offset(dst) + 5;
	}
};
constexpr const std::array<thread::instruction, 256> ops_init() {
	std::array<thread::instruction, 256> ops = {nullptr};
		// SET HALT
		for (uint32_t i=0; i<ops.size(); i++) {
			ops[i] = nullptr;
		}
		// 0x0.. : SPECIAL
		ops[0x00] = &thread::halt;
		ops[0x01] = &thread::nop;
		// 0x1.. : LOAD STORE
		ops[0x11] = &thread::load_code;
		ops[0x12] = &thread::load_code_array;
		ops[0x13] = &thread::load_data;
		ops[0x14] = &thread::load_data_array;
		ops[0x15] = &thread::load_stack;
		ops[0x16] = &thread::load_stack_array;
		ops[0x17] = &thread::store_data;
		ops[0x18] = &thread::store_data_array;
		ops[0x19] = &thread::store_stack;
		ops[0x1a] = &thread::store_stack_array;
		// 0x02.. : STACK MANIPULATION
		ops[0x20] = &thread::push;
		ops[0x21] = &thread::push_array;
		ops[0x22] = &thread::pop;
		ops[0x23] = &thread::pop_array;
		ops[0x24] = &thread::dup;
		ops[0x25] = &thread::dup_array;
		ops[0x26] = &thread::swap;
		ops[0x27] = &thread::swap_array;
		// 0x3.. : ARITHMETIC
		ops[0x30] = &thread::iadd;
		ops[0x31] = &thread::fadd;
		ops[0x32] = &thread::isub;
		ops[0x33] = &thread::fsub;
		ops[0x34] = &thread::imul;
		ops[0x35] = &thread::fmul;
		ops[0x36] = &thread::idiv;
		ops[0x37] = &thread::fdiv;
		ops[0x38] = &thread::irem;
		ops[0x39] = &thread::ineg;
		ops[0x3a] = &thread::fneg;
		// 0x4.. : TYPE CONVERSION
		ops[0x40] = &thread::i2f;
		ops[0x41] = &thread::f2i;
		// 0x5.. : JUMP
		ops[0x50] = &thread::jump;     
		ops[0x51] = &thread::ifeq_jump;
		ops[0x52] = &thread::iflt_jump;
		ops[0x53] = &thread::ifgt_jump;
		ops[0x54] = &thread::ifle_jump;
		ops[0x55] = &thread::ifge_jump;
		ops[0x56] = &thread::ifne_jump;
		// 0x6.. : FUNCTION CALL
		ops[0x60] = &thread::push_fp;
		ops[0x61] = &thread::call_fp;
		ops[0x62] = &thread::return0;
		ops[0x63] = &thread::return1;
		ops[0x64] = &thread::return1_array;
	return ops;
}
std::array<thread::instruction, 256> thread::ops = ops_init();
#endif
