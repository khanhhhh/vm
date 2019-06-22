#ifndef _I_DATA_HH_
#define _I_DATA_HH_
template<class utype>
class i_data {
public:
	i_data() {}
	virtual ~i_data() {}
	virtual utype	load(utype addr) const = 0;
	virtual void	store(utype addr, utype v) = 0;

	virtual void	load_array(utype addr, utype len, utype *v) const = 0;
	virtual void	store_array(utype addr, utype len, utype *v) = 0;
};
#endif
