#ifndef _CODE_HH_
#define _CODE_HH_
#include"i_code.hh"
#include<cstring>
#include<cstdlib>
template<class opcode, class utype, utype count>
class code: public i_code<opcode, utype> {
public:
	opcode mem[count];
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
		std::memcpy(&out, mem + addr, sizeof(utype));
		return out;
	}
	void	fetch_array(utype base, utype len, utype *out) const {
		std::memcpy(out, mem + base, len * sizeof(utype));
	}
};
#endif
