#ifndef _THREAD_HH_
#define _THREAD_HH_
#include"i_thread.hh"
#include"code.hh"
#include"data.hh"
template<class opcode, class dtype>
class thread: i_thread<opcode, dtype> {
private:
	dtype 
public:
	thread(const i_code<opcode, dtype>& c, i_data<dtype>& d): i_thread<opcode, dtype>(c, d) {}
	virtual ~thread() {}
	virtual bool iterate() = 0;
};
#endif
