#ifndef __BASIC_H
#define __BASIC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define BUF_SIZE 1024

#define TRUE 1
#define FALSE 0
typedef int BOOL;

/*
 * returns negative if arg1 < arg2
 *			  0 if arg1 == arg2
 *		   positive if arg1 > arg2 
 */
typedef int (*compare_func)(const void *arg1, const void *arg2);

/*
 * normally, this method is provided to apply an operation to each element in
 * container, now, modification of the element is not allowed.
 */
typedef void (*foreach_func)(const void *arg);

/*
 * if the pointer that being inserted(appended) is created by method like
 * 'malloc'(or similar), and you wish the memory will be freed when list(vector)
 * destroyed, please provide release_func(most likely, just method 'free'),
 * otherwise, just put release_func NULL.
 *
 * once provided release_func, the same pointer can't be added into container
 * more than one time, or cause DOUBLE-FREE-ERROR
 */
typedef void (*release_func)(void *arg);

#endif
