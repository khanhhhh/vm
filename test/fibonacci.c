#include<stdio.h>
#include<stdint.h>
int32_t fib(int32_t x) {
/* fib:	   load stack 0	//x
	 * load code 2	//2
	 * isub		//x-2
	 * ifgt jump B1;//->free stack
	 * B0:
	 * 	load code 1
	 * 	return1
	 * B1:
	 * 	load code 0	//temp0
	 *	push_fp
	 * 	load stack 0	//x
	 * 	load code 1	//1
	 * 	isub		//x-1
	 *	call_fp `fib`	// -> override temp0
	 *
	 * 	load code 0	//temp1
	 *	push_fp
	 * 	load stack 0	//x
	 * 	load code 2	//2
	 * 	isub		//x-2
	 *	call_fp `fib`	// -> override temp0
	 *	
	 *	iadd		//temp0 + temp1
	 *	return1
	 * */
	if (x-2 <= 0) {
		return 1;
	}
	else {
		uint32_t temp0 = fib(x-1);
		uint32_t temp1 = fib(x-2);
		return temp0 + temp1;
	}
}
int main() {
	/* load code 0 //temp0
	 * push_fp
	 * load code 20
	 * call_fp `fib` // -> override temp0
	 * print_int
	 * */
	int32_t temp0 = fib(20);
	printf("%d\n", temp0);
}
