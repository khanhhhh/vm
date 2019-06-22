#ifndef _I_THREAD_HH_
#define _I_THREAD_HH_
#include"i_code.hh"
#include"i_data.hh"
template<class opcode, class utype>
class i_thread {
protected:
const	i_code<opcode, utype>& c;
	i_data<utype>& d;
public:
	i_thread(const i_code<opcode, utype>& c, i_data<utype>& d): c(c), d(d) {}
	virtual ~i_thread() {}
	virtual bool iterate() = 0;
};
#endif
