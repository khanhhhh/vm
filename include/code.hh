#ifndef _CODE_HH_
#define _CODE_HH_
#include"i_code.hh"
#include<cstring>
#include<array>
template<class opcode, class utype, utype count>
class code: public i_code<opcode, utype> {
public:
	std::array<opcode, count> mem;
public:
	code():
		i_code<opcode, utype>()
	{}
	~code() {
	}
	opcode	fetch(utype addr) const {
		return mem[addr];
	}
	utype	fetch_param(utype addr) const {
		utype out;
		std::memcpy(&out, mem.data() + addr, sizeof(utype));
		return out;
	}
	void	fetch_array(utype base, utype len, utype *out) const {
		std::memcpy(out, mem.data() + base, len * sizeof(utype));
	}
};
#endif
