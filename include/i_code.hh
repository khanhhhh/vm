#ifndef _I_CODE_HH_
#define _I_CODE_HH_
template <class opcode, class utype>
class i_code {
public:
	i_code() {}
	virtual ~i_code() {}
	virtual opcode	fetch(utype addr) const = 0;
	virtual utype	fetch_param(utype addr) const = 0;
	virtual void	fetch_array(utype base, utype len, utype *out) const = 0;
};
#endif
