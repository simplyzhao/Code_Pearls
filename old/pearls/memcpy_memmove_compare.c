/* 问题1: 指针能否比较大小? */
/* 针对问题1的解答: 
 * 可以比较大小，条件是两个指针指向同一个数组中的元素(也适用于使用malloc函数动态分配获得的内存)
 *
 * 指针运算:
 * a. 指针 +- 整数，适用于指向数组中某个元素的指针
 * b. 指针 - 指针，两个指针必须指向同一个数组中的元素
 * c. 指针 cmp(>, <, >=, <=) 指针，两个指针必须指向同一个数组中的元素
 *
 * 注意: 指针可以指向数组最后一个元素后面的那个位置，但对此不能执行间接访问
 */

/* 问题2: memcpy与memmove的区别 */
/* 针对问题2的解答:
 * 函数原型:
 * void *memcpy(void *dst, const void *src, size_t num)
 * void *memmove(void *dst, const void *src, size_t num)
 *
 * 简单来说，memmove是把一堆byte从src移到dst，memcpy是把一堆byte从 src拷贝到dst
 * 最大不同的是：memmove是先把一堆byte拷贝到一个临时的array中，然后再把这个临时的array写到dst中去；
 * 而 memcpy没有这个逻辑，直接就是从src一个一个字节的读，同时往dst一个一个字节的写。这样就导致了一个最根本的不同： 
 * memcpy不适合或者说不能处理src和dst两块内存有重叠（overlap）的情况。
 * 因为memcpy是直接从src拷贝，然后往dst中写，这样，如果src和dst两块内存有重叠，这样就会导致写数据出错了。比如： 
		src.........\0
			dst.........\0
 * 这样的情况，由于dst和src有重叠的部分，这样，在写dst的时候，同时就把src中的内容也改写了，这样拷贝出来的东西就不对了。
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int
main(int argc, char **argv)
{
	char buf1[] = "i'm joey.zhao, taobaobao";
	memmove(buf1+4, buf1, 6);
	printf("%s\n", buf1);
	char buf2[] = "i'm joey.zhao, taobaobao";
	memcpy(buf2+4, buf2, 6);
	printf("%s\n", buf2);

	return 0;
}

/* possible memmove implementation, untested */
void *
_Memmove(void *dst, const void *src, size_t count)
{
	void *ret = dst;
	if(dst == src)
		return;
	if((char *)dst>(char *)src && (char *)dst<(char *)src+count) { /* overlapping */
		dst = (char *)dst + count - 1;
		src = (char *)src + count - 1;
		while(count--) {
			*(char *)dst = *(char *)src;
			dst = (char *)dst - 1;
			src = (char *)src - 1;
		}
	} else {
		while(count--) {
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
	}
	return ret;
}
