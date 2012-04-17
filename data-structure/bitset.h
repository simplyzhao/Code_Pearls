#ifndef __BITSET_H
#define __BITSET_H

/* implementation of bitset */

#include "basic.h"

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F

struct Bitset;

struct Bitset *create_bitset(int bits);
void destroy_bitset(struct Bitset *bitset);

void bitset_set(struct Bitset *bitset, int bit_pos);
void bitset_clear(struct Bitset *bitset, int bit_pos);
void bitset_reverse(struct Bitset *bitset, int bit_pos);
BOOL bitset_test(struct Bitset *bitset, int bit_pos);

#endif
