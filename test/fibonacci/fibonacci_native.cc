#include<cstdio>
int fib(int x) {
	if (x<=2) {
		return 1;
	} else {
		return fib(x-1) + fib(x-2);
	}
}
int main() {
	int res = fib(35);
	std::printf("%d\n", res);
	return 0;
}
