#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/slab.h>
#include "encoder.h"

/* Initialize the struct */
int init_encoding(Data *d, size_t size)
{
	d->bin = kmalloc(size*sizeof(int), GFP_ATOMIC);
	if (d->bin == NULL) {
		return -ENOMEM;
	}

	d->encoded_bin = kmalloc(size*sizeof(int), GFP_ATOMIC);
	if (d->encoded_bin == NULL) {
		kfree(d->bin);
		return -ENOMEM;
	}
	
	d->count = 0;
	d->num_i = 0;

	return 0;
}

/* Convert data to binary */
int *conv_to_bin(unsigned int val, int *retval, int size)
{
	int i, k;

	for (i = size; i >= 0; i--) {
		k = val >> i;
		if (k & 1) retval[i] = 1;
		else retval[i] = 0;
	}

	return retval;
}

/* Build binary array */
void build_bin_array(Data *d, int length, int position)
{
	int i;

	for (i = position; i < length+position; i++) {
		d->encoded_bin[i] = d->bin[i-position];
	}
}

/* Encode the binary data */
void encode_bin(Data *d, int flag)
{
	int i;
	int j;

	if (flag) {
		/* Encode binary - do bitstuffing */
		for (i = 0; i < d->count; i++) {
			if (d->encoded_bin[i] == 0) {
				d->num_i = 0;
			}
			else {
				d->num_i++;
				if (d->num_i == 5) {
					for (j = d->count; j >= i-1; j--) {
						d->encoded_bin[j+1] = d->encoded_bin[j];
					}
					d->encoded_bin[i+1] = 0;
					d->count++;
				}
			}
		}
	} else {
		// No bit-stuffing
		for (i = 0; i < d->count; i++) {
			d->encoded_bin[i] = d->bin[i];
		}
	}
}

/* Free any reserved memory for struct */
void destroy(Data *d)
{
	if (d) {
		kfree(d);
	}
}
