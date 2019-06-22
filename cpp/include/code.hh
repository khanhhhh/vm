#ifndef _CODE_HH_
#define _CODE_HH_
#include"i_code.hh"
#include<cstring>
#include<cstdlib>
template<class opcode, class utype>
class code: i_code<opcode, utype> {
public:
	opcode *mem;
public:
	code(utype count):
		i_code<opcode, utype>(),
		mem((opcode*)std::malloc(count * sizeof(opcode)))
	{}
	~code() {
		std::free(mem);
	}
	opcode	fetch(utype addr) const {
		return mem[addr];
	}
	utype	fetch_param(utype addr) const {
		utype out;
		std::memcpy(&out, mem + addr, sizeof(utype));
		return out;
	}
};
#endif
