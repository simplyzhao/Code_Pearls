#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FULL_MASK 0xff
#define HALF_BITS_LENGTH 4
#define GRIDW 3
#define LMASK (FULL_MASK << HALF_BITS_LENGTH) /* 0xf0 */
#define RMASK (FULL_MASK >> HALF_BITS_LENGTH) /* 0x0f */
#define LGET(arg) (((arg) & LMASK)>>HALF_BITS_LENGTH)
#define RGET(arg) ((arg) & RMASK)
#define LSET(arg, v) ((arg) = (((arg)&RMASK) | (((v)&RMASK)<<HALF_BITS_LENGTH)))
#define RSET(arg, v) ((arg) = (((arg)&LMASK) | ((v)&RMASK)))
typedef unsigned char byte;

void
naive()
{	
	byte x;

	for(LSET(x, 1); LGET(x)<=GRIDW*GRIDW; LSET(x, LGET(x)+1)) 
		for(RSET(x, 1); RGET(x)<=GRIDW*GRIDW; RSET(x, RGET(x)+1)) 
			if(LGET(x)%GRIDW != RGET(x)%GRIDW)
				fprintf(stdout, "A = %d, B = %d\n", LGET(x), RGET(x));
}

struct Trick {
	unsigned char a : 4;
	unsigned char b : 4;
};

void 
tricky()
{
	struct Trick t;
	for(t.a=1; t.a<=GRIDW*GRIDW; ++t.a)
		for(t.b=1; t.b<=GRIDW*GRIDW; ++t.b)
			if(t.a%GRIDW != t.b%GRIDW)
				fprintf(stdout, "A = %d, B = %d\n", t.a, t.b);
}

int
main(int argc, char **argv)
{
	fprintf(stdout, "NAIVE\n");
	naive();
	fprintf(stdout, "TRICKY\n");
	tricky();
	return 0;
}
