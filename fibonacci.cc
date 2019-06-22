#include"thread.hh"
#include<iostream>
#include<fstream>
#include<cstdint>
#include<ctime>
std::vector<uint8_t> read_file(const std::string& filename) {
	std::ifstream f(filename);
	f.seekg(0, f.end);
	size_t length = f.tellg();
	f.seekg(0, f.beg);

	std::vector<uint8_t> out(length);
	f.read((char*)out.data(), length);
	return out;
}
int main() {
	/*
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
		0x61, 0x06, 0x00, 0x00, 0x00,                   // #69 call_fp `fib`
		0x17, 0x00, 0x00, 0x00, 0x00,			// #74 store_data 0
		0x00						// #78 halt
	};
	int len = 79;
	program p(len);
	std::memcpy(p.mem, source, len);
	*/
	std::vector<uint8_t> source = read_file("fibonacci");
	program p(source.size());
	std::memcpy(p.mem, source.data(), source.size());


	heap h(1);
	h.store(0, 20);

	thread t(p, h);
        long t1 = std::clock();
        long count = 0;
	while (t.iterate())
		count++;
        long t2 = std::clock();
	std::printf("\nMIPS: %f\n", 1e-6 * (double)count * CLOCKS_PER_SEC / (t2-t1));


	std::cout<<h.load(0)<<std::endl;
	return 0;
}