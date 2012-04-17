#ifndef __VECTOR_H
#define __VECTOR_H

/* 
 * implementation of vector 
 * Note:
 * you have the capability to control whether or not to release the memory related
 * to the pointer when remove it from the vector
 * if you wanna, provide a 'release_func', plus set 'mem_release' TRUE in
 * destroy and remove methods, otherwise, you just have to take care of the
 * memory yourself
 */

#include "basic.h"

#define DEFAULT_CAPACITY 8

struct Vector;

struct Vector *create_vector(int default_capacity, release_func);
void destroy_vector(struct Vector *, BOOL mem_release);

BOOL vector_push_back(struct Vector *, void *);
BOOL vector_push_front(struct Vector *, void *);
BOOL vector_insert(struct Vector *, void *, int);
BOOL vector_remove(struct Vector *, void *, compare_func, BOOL mem_release);
BOOL vector_remove_at(struct Vector *, int, BOOL mem_release);
BOOL vector_exchange(struct Vector *, int, int);
struct Vector *vector_duplicate(struct Vector *);

void *vector_at(struct Vector *, int);
int vector_indexof(struct Vector *, void *, compare_func);
void vector_foreach(struct Vector *, foreach_func);
int vector_count(struct Vector *);
int vector_capacity(struct Vector *);

BOOL vector_shuffle(struct Vector *);
BOOL vector_sort(struct Vector *, compare_func);
/* 
 * the following three methods(O(logN)):
 * precondition
 * vector is sorted(method vector_sort called, and return TRUE)
 *
 * postcondition:
 * return random(bsearch), last(upper), first(lower) index 
 * which vector[index]=target if target exists in current vector, or return -1
 */
int vector_bsearch(struct Vector *, const void *, compare_func);
int vector_upper(struct Vector *, const void *, compare_func);
int vector_lower(struct Vector *, const void *, compare_func);

#endif
