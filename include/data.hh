#ifndef _DATA_HH_
#define _DATA_HH_
#include"i_data.hh"
#include<cstring>
template<class utype, utype count>
class data: public i_data<utype> {
public:
	std::array<utype, count> mem;
public:
	data():
		i_data<utype>()
	{}
	~data() {
	}
	utype	load(utype addr) const {
		return mem[addr];
	}
	void	store(utype addr, utype v) {
		mem[addr] = v;
	}

	void	load_array(utype addr, utype len, utype *v) const {
		std::memcpy(v, mem.data() + addr, len *sizeof(utype));
	}
	void	store_array(utype addr, utype len, utype *v) {
		std::memcpy(mem.data() + addr, v, len * sizeof(utype));
	}
};
#endif
