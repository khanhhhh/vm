#include"thread.hh"
#include<cstring>
#include<cstdint>
#include<ctime>
int main() {
	uint8_t source[] = {
		// int main()
		0x00, 0x00, 0x00, 0x00, 0x00,	// nop				#0
		0x1d,				// push_fp			#5
		0x01, 0x1e, 0x00, 0x00, 0x00,	// load code 30			#6
		0x1e, 0x12, 0x00, 0x00, 0x00,	// call_fp `fib`		#11
		0xfc,				// print_int			#16
		0xff,				// halt				#17
		//int fib(int x);
		// if (x - 2 > 0) goto else.
		0x03, 0x00, 0x00, 0x00, 0x00,	// load stack 0 //x		#18
		0x01, 0x02, 0x00, 0x00, 0x00,	// load code 2			#23
		0x0b,				// isub				#28
		0x19, 0x28, 0x00, 0x00, 0x00,	// ifgt_jump B1			#29
			//then return 1;
			0x01, 0x01, 0x00, 0x00, 0x00,	// load code 1 (B0)	#34
			0x20,				// return1		#39
			//else return fib(x-1) + fib(x-2)
			0x00, 0x00, 0x00, 0x00, 0x00,	// nop (B1)		#40
			0x1d,				// push_fp		#45
			0x03, 0x00, 0x00, 0x00, 0x00,	// load stack 0		#46
			0x01, 0x01, 0x00, 0x00, 0x00,	// load code 1		#51
			0x0b,				// isub			#56
			0x1e, 0x12, 0x00, 0x00, 0x00,   // call_fp `fib`	#57

	                0x00, 0x00, 0x00, 0x00, 0x00,   // nop (B1)		#62
        	        0x1d,                           // push_fp		#67
                	0x03, 0x00, 0x00, 0x00, 0x00,   // load stack 0		#68
			0x01, 0x02, 0x00, 0x00, 0x00,	// load code 2		#73
			0x0b,				// isub			#78
			0x1e, 0x12, 0x00, 0x00, 0x00,	// call_fp `fib`	#79
			0x09,				// iadd			#84
			0x20,				// return1		#85
	};
	int len = 86;

	program p(86); std::memcpy(p.mem, source, 86 * sizeof(uint8_t));
	heap h(0);
	thread t(p, h);

        long t1 = std::clock();
        long count = 0;
	while (t.iterate())
		count++;
        long t2 = std::clock();
        printf("\nMIPS: %f\n", 1e-6 * (double)count * CLOCKS_PER_SEC / (t2-t1));





	return 0;
}
