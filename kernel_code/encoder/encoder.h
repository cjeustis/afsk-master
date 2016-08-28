#ifndef ENCODER_H
#define ENCODER_H

typedef struct {
	int *bin;
	int *encoded_bin;
	int count;
	int num_i;
} Data;

int init_encoding(Data *d, size_t size);
int *conv_to_bin(unsigned int val, int *retval, int size);
void build_bin_array(Data *d, int length, int position);
void encode_bin(Data *d, int flag);
void destroy(Data *d);

#endif