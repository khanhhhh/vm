#include"data.h"
data	data_new(object *mem) {
	data d;
	d.mem = mem;
	return d;
}
void	data_del(data *d) {}
object	data_load(data *d, uint32_t offset) {
	return d->mem[offset];
}
void	data_store(data *d, uint32_t offset, object item) {
	d->mem[offset] = item;
}
