#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Diff(a, b) ((a)>(b) ? ((a)-(b)) : ((b)-(a)))
#define Max(a, b) ((a)>(b) ? (a) : (b))
#define MAX_LEN 3
typedef enum {
	Black,
	White
}Color;

int
is_linear(char *src, char *dst)
{
	if(src[0]==dst[0] || src[1]==dst[1])
		return 1;
	return 0;
}

int 
is_oblique(char *src, char *dst)
{
	int x_diff = Diff(src[0], dst[0]);
	int y_diff = Diff(src[1], dst[1]);
	if(x_diff == y_diff)
		return 1;
	return 0;
}

Color
black_or_white(char *src)
{
	int x = src[0] - 'a' + 1;
	int y = src[1] - '0';
	if(x%2 == y%2)
		return White;
	return Black;
}

void
solve(char *src, char *dst)
{
	int a, b, c, d, x_diff, y_diff;
	x_diff = Diff(src[0], dst[0]);
	y_diff = Diff(src[1], dst[1]);
	a = Max(x_diff, y_diff); /* king */
	if(is_linear(src, dst) || is_oblique(src, dst)) /* queen */
		b = 1;
	else 
		b = 2;

	if(is_linear(src, dst)) /* rook */
		c = 1;
	else 
		c = 2;

	if(is_oblique(src, dst)) /* bishop */
		d = 1;
	else if(black_or_white(src) != black_or_white(dst))
		d = -1;
	else
		d = 2;

	printf("%d %d %d ", a, b, c);
	if(d == -1)
		printf("Inf\n");
	else
		printf("%d\n", d);
}

int
main(int argc, char **argv)
{
	int tests;
	char begin[MAX_LEN], end[MAX_LEN];
	scanf("%d", &tests);
	while(tests--) {
		scanf("%s %s", begin, end);
		if(begin[0]==end[0] && begin[1]==end[1])
			printf("0 0 0 0\n");
		else
			solve(begin, end);
	}
}
