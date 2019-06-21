#include"thread.h"
#include<stdio.h>
static inline int32_t f2i_push(float f) {
	int *ptr = (int*)&f;
	return *ptr;
}
static inline int32_t l2i_push_first(int64_t l) {
	int32_t *ptr = (int32_t*)&l;
	return ptr[1];
}
static inline int32_t l2i_push_last(int64_t l) {
	int32_t *ptr = (int32_t*)&l;
	return ptr[0];
}
static inline int32_t d2i_push_first(double d) {
	int32_t *ptr = (int32_t*)&d;
	return ptr[1];
}
static inline int32_t d2i_push_last(double d) {
	int32_t *ptr = (int32_t*)&d;
	return ptr[0];
}
int main() {

	printf("0x%x\n", f2i_push(2));

	return 0;
}
