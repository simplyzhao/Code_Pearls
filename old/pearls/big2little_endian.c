/*
 * Question:
 * 1. how to identify one computer's byte order, big endian or little endian?
 * 2. transfer from big endian to little endian
 *
 * Example:
 *
 * Solution:
 *
 * See Also:
 * htons, htonl, ntohs, ntohl
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define BIG2LITTLE16(X) ((((uint16)(X)&0xff00)>>8) | (((uint16)(X)&0x00ff)<<8))
#define BIG2LITTLE32(X) ((((uint32)(X) & 0xff000000)>>24) | \
						 (((uint32)(X) & 0x00ff0000)>>8) | \
						 (((uint32)(X) & 0x000000ff)<<24) | \
						 (((uint32)(X) & 0x0000ff00)<<8))

union X {
	unsigned int i;
	struct Y {
		unsigned char a;
		unsigned char b;
		unsigned char c;
		unsigned char d;
	} y;
} x;

int
main(int argc, char **argv)
{
	x.i = 0x12345678;
	printf("a=%x, b=%x, c=%x, d=%x\n", x.y.a, x.y.b, x.y.c, x.y.d);
	printf("%s\n", x.y.a==0x78 ? "Little Endian" : "Big Endian");

	x.i = BIG2LITTLE32(x.i);
	printf("a=%x, b=%x, c=%x, d=%x\n", x.y.a, x.y.b, x.y.c, x.y.d);

	return 0;
}
