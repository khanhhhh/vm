#include"thread.hh"
#include<iostream>
#include<cstdint>
#include<ctime>

/* def fib(x: int) -> int {
 * 	stack.push(1);
 * 	stack.push(1);
 * 	do {
 * 		a, b = stack.end();
 * 		next_num = a + b;
 * 		stack.push(next_num)
 *		x -= 1;
 * 	} while (x > 0)
 * 	return x;
 * }
 * */
int main() {
	uint8_t source[] = {
		0x13, 0x00, 0x00, 0x00, 0x00,	//#0  load_data 0
		0x11, 0x01, 0x00, 0x00, 0x00,	//#5  load_code 1
		0x24,				//#10 dup

		0x25, 0x02, 0x00, 0x00, 0x00,	//#11 dup_array 2 [while]
		0x30,				//#16 iadd
		0x15, 0x00, 0x00, 0x00, 0x00,	//#17 load_stack 0
		0x11, 0x01, 0x00, 0x00, 0x00,	//#22 load_code 1
		0x32,				//#27 isub
		0x24,				//#28 dup
		0x19, 0x00, 0x00, 0x00, 0x00,	//#29 store_stack 0
		0x53, 0x0b, 0x00, 0x00, 0x00,	//#34 ifgt_jump `while`
		0x17, 0x00, 0x00, 0x00, 0x00	//#39 store_data 0

	};
	int len = 43;
	program p(len);
	std::memcpy(p.mem, source, len);

	heap h(1);
	h.mem[0] = 28;

	thread t(p, h);
        long t1 = std::clock();
        long count = 0;
	while (t.iterate())
		count++;
        long t2 = std::clock();
	std::printf("\nMIPS: %f\n", 1e-6 * (double)count * CLOCKS_PER_SEC / (t2-t1));


	std::cout<<h.mem[0]<<std::endl;
	return 0;
}
