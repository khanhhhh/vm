#ifndef _DATA_HH_
#define _DATA_HH_
#include"i_data.hh"
#include<vector>
template<class utype>
class data: public i_data<utype> {
private:
	utype *mem;
public:
	data(utype count):
		i_data<utype>(),
		mem((utype*)std::malloc(count * sizeof(utype)))
	{}
	~data() {
		std::free(mem);
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
