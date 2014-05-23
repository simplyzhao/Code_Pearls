#include "bitset.h"

struct Bitset {
	int bits_capacity;
	int words_capacity;
	int *words;
};

struct Bitset *
create_bitset(int bits)
{
	struct Bitset *bitset = (struct Bitset *)malloc(sizeof(struct Bitset));
	if(bitset != NULL) {
		bitset->bits_capacity = bits;
		bitset->words_capacity = bits/BITSPERWORD + 1;
		bitset->words = (int *)malloc(sizeof(int) * (bitset->words_capacity));

		if(bitset->words == NULL) {
			free(bitset);
			bitset = NULL;
		} else 
			memset(bitset->words, 0, sizeof(int)*(bitset->words_capacity));
	}
	return bitset;
}

void
destroy_bitset(struct Bitset *bitset)
{
	if(bitset) {
		if(bitset->words)
			free(bitset->words);

		free(bitset);
	}
}

void
bitset_set(struct Bitset *bitset, int bit_pos)
{
	assert(bitset != NULL);
	if(bit_pos>=0 && bit_pos<bitset->bits_capacity)
		bitset->words[bit_pos>>SHIFT] |= (1<<(bit_pos & MASK));
}

void
bitset_clear(struct Bitset *bitset, int bit_pos)
{
	assert(bitset != NULL);
	if(bit_pos>=0 && bit_pos<bitset->bits_capacity)
		bitset->words[bit_pos>>SHIFT] &= (~(1<<(bit_pos & MASK)));
}

void
bitset_reverse(struct Bitset *bitset, int bit_pos)
{
	assert(bitset != NULL);
	if(bit_pos>=0 && bit_pos<bitset->bits_capacity)
		bitset->words[bit_pos>>SHIFT] ^= (1<<(bit_pos & MASK));
}

BOOL
bitset_test(struct Bitset *bitset, int bit_pos)
{
	assert(bitset != NULL);
	if(bit_pos>=0 && bit_pos<bitset->bits_capacity)
		if(bitset->words[bit_pos>>SHIFT] & (1<<(bit_pos & MASK)))
			return TRUE;
	return FALSE;
}
