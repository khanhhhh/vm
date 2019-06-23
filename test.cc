#include"thread.hh"
template<uint32_t count> using code1 = code<uint8_t, uint32_t, count>;
int main() {
	code1<1> c;


	return 0;
}
