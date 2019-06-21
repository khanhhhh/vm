#ifndef _DATA_HH_
#define _DATA_HH_
#include"i_data.hh"
#include<vector>
template<class dtype>
class data: public i_data<dtype> {
private:
	std::vector<dtype> mem;
public:
	data(): i_data<dtype>(), mem() {}
	~data() {}
	dtype	load(dtype offset) const {
		return mem[offset];
	}
	void	store(dtype offset, dtype v) {
		mem[offset] = v;
	}
	void	push_data(dtype v) {
		mem.push_back(v);
	}
};
#endif
