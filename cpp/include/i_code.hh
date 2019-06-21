#ifndef _I_CODE_HH_
#define _I_CODE_HH_
template <class opcode, class dtype>
class i_code {
public:
	i_code() {}
	virtual ~i_code() {}
	virtual opcode	fetch(dtype offset) const = 0;
	virtual dtype	fetch_param(dtype offset) const = 0;
};
#endif
