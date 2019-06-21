#ifndef _I_DATA_HH_
#define _I_DATA_HH_
template<class dtype>
class i_data {
public:
	i_data() {}
	virtual ~i_data() {}
	virtual dtype	load(dtype offset) const = 0;
	virtual void	store(dtype offset, dtype v) = 0;
};
#endif
