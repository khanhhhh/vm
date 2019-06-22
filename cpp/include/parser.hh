#ifndef _PARSER_HH_
#define _PARSER_HH_
#include"i_parser.hh"
class parser: public i_parser {
public:
	parser(): i_parser() {}
	~parser() {}
	std::string<uint8_t> parse(const std::string& source) {
	
	}
private:
	enum token {
		halt,
		nop,
		load_code, load_code_array,
		load_data, load_data_array,
		load_stack, loat_stack_array,
		store_data, store_data_array,
		store_stack, store_stack_array,
		push, push_array,
		pop, pop_array,
		dup, dup_array,
		swap, swap_array,
		iadd, fadd,
		isub, fsub,
		imul, fmul,
		idiv, fdiv,
		irem,
		ineg,
		fneg,
		i2f, f2i,
		jump,
		ifeq_jump,
		iflt_jump,
		ifgt_jump,
		ifle_jump,
		ifge_jump,
		ifne_jump,
		push_fp,
		call_fp,
		return0,
		return1,
		return1_array,
		print_int,
		print_float,
		print_char
	};
};
#endif
