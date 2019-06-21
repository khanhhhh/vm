#ifndef _DATA_H_
#define _DATA_H_
#include"object.h"
typedef struct data_t {
	object *mem;
} data;
// CONSTRUCTOR
data	data_new(object *mem);
// DESTRUCTOR
void	data_del(data *d);
// DATA OP
object	data_load(data *d, uint32_t offset);
void	data_store(data *d, uint32_t offset, object item);
#endif
