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
	std::vector<uint8_t> source = read_file("fibonacci.byte");





















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
