#ifndef _DATA_HH_
#define _DATA_HH_
#include"i_data.hh"
#include<vector>
template<class utype, utype count>
class data: public i_data<utype> {
public:
	utype mem[count];
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
		std::memcpy(v, mem + addr, len *sizeof(utype));
	}
	void	store_array(utype addr, utype len, utype *v) {
		std::memcpy(mem+addr, v, len * sizeof(utype));
	}
};
#endif
