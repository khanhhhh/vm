#ifndef _CODE_HH_
#define _CODE_HH_
#include"i_code.hh"
#include<cstdint>
#include<cstring>
#include<vector>
template<class opcode, class dtype>
class code: i_code<opcode, dtype> {
private:
	std::vector<opcode> mem;
public:
	code(): i_code<opcode, dtype>(), mem() {}
	~code() {}
	opcode	fetch(dtype offset) const {
		return mem[offset];
	}
	dtype	fetch_param(dtype offset) const {
		dtype out;
		std::memcpy(&out, mem.data() + offset, sizeof(dtype));
		return out;
	}
	void	push_opcode(opcode o) {
		mem.push_back(o);
	}
	void	push_param(dtype v) {
		void *base = mem.data();
		for (int i=0; i<(sizeof(dtype)/sizeof(opcode)); i++) {
			mem.push_back(0);
		}
		std::memcpy(base, &v, sizeof(dtype));
	}
};
#endif
