#ifdef _WIN32
#include<Windows.h>
#else
#include<ctime>
#endif
#include<cstdint>
class timer
{
	private:
	#ifdef _WIN32
	static int64_t freq;
	#endif
	public:
	timer()
	{
		#ifdef _WIN32
		if (0 == freq)
			QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		#endif
	}
	~timer()
	{}
	inline int64_t now()
	{
		int64_t time_point;
		#ifdef _WIN32
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		time_point = 1000000000*t.QuadPart/freq;
		#else
		timespec tp;
		clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
		time_point = static_cast<int64_t>(1000000000*tp.tv_sec) + static_cast<int64_t>(tp.tv_nsec);
		#endif
		return time_point;
	}
	static inline double elapsed_time(int64_t t2, int64_t t1)
	{
		return static_cast<double>(t2-t1);
	}
};
#ifdef _WIN32
int64_t timer::freq = 0;
#endif
