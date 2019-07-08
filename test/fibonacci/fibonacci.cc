#include"thread.hh"
#include<iostream>
#include<cstdint>
#include<ctime>
/* def fib(x: int) -> int {
 *	if (x <= 2) {
 *		return 1;
 *	} else {
 *		return fib(x-1) + fib(x-2);
 *	}
 * }
 * */


int main() {
	uint8_t source[] = {
		// int main()
		0x01,						// #0  nop
		0x50, 0x40, 0x00, 0x00, 0x00,			// #1  jump `main`

		0x15, 0x00, 0x00, 0x00, 0x00,			// #6  load_stack 0	[fib]
		0x11, 0x02, 0x00, 0x00, 0x00,			// #11 load_code 2
		0x32, 						// #16 isub
		0x53, 0x1c, 0x00, 0x00, 0x00,			// #17 ifgt_jump `b1`

		0x11, 0x01, 0x00, 0x00, 0x00,			// #22 load_code 1	[b0]
		0x63,						// #27 return1

		0x60,						// #28 push_fp 		[b1]
		0x15, 0x00, 0x00, 0x00, 0x00,			// #29 load_stack 0
		0x11, 0x01, 0x00, 0x00, 0x00,                   // #34 load_code 1
		0x32,                                           // #39 isub
		0x61, 0x06, 0x00, 0x00, 0x00,			// #40 call_fp `fib`

		0x60,						// #45 push_fp
		0x15, 0x00, 0x00, 0x00, 0x00,			// #46 load_stack 0
		0x11, 0x02, 0x00, 0x00, 0x00,                   // #51 load_code 2
		0x32,                                           // #56 isub
		0x61, 0x06, 0x00, 0x00, 0x00,			// #57 call_fp `fib`

		0x30,						// #62 iadd
		0x63,						// #63 return1

		0x60,						// #64 push_fp		[main]
		0x13, 0x00, 0x00, 0x00, 0x00,			// #65 load_data 0
		0x61, 0x06, 0x00, 0x00, 0x00,                   // #70 call_fp `fib`
		0x17, 0x00, 0x00, 0x00, 0x00,			// #75 store_data 0
		0x00						// #80 halt
	};
	constexpr int len = 81;
	program<len> p;
	std::memcpy(p.mem.data(), source, len);

	heap<1> h;
	h.mem[0] = 35;
	thread t(p, h);
    long t1 = std::clock();
    long count = 0;
	while (t.iterate())
		count++;
    long t2 = std::clock();
	std::printf("ops: %ld, ticks: %ld\n", count, t2-t1);
	std::printf("MIPS: %f\n", 1e-6 * (double)count * CLOCKS_PER_SEC / (t2-t1));

	std::cout<<h.mem[0]<<std::endl;
	return 0;
}
