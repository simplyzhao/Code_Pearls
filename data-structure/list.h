#ifndef __LIST_H
#define __LIST_H

/* 
 * implementation of doubly linked list (unordered) 
 * Note:
 * you have the capability to control whether or not to release the memory related
 * to the pointer when remove it from the list
 * if you wanna, provide a 'release_func', plus set 'mem_release' TRUE in
 * destroy and remove methods, otherwise, you just have to take care of the
 * memory yourself
 */

#include "basic.h"

struct Node {
	void *val;
	struct Node *pre, *next;
};

struct List;

struct List *create_list(release_func);
void destroy_list(struct List *, BOOL mem_release);

BOOL list_push_back(struct List *, void *);
BOOL list_push_front(struct List *, void *);
BOOL list_insert_after(struct List *, struct Node *, void *);
BOOL list_insert_before(struct List *, struct Node *, void *);
BOOL list_remove(struct List *, void *, compare_func, BOOL mem_release);
BOOL list_remove_node(struct List *, struct Node *, BOOL mem_release);

struct Node *list_find(struct List *, const void *, compare_func);
struct Node *list_head(struct List *);
struct Node *list_tail(struct List *);
void list_foreach(struct List *, foreach_func apply);
void list_foreach_back(struct List *, foreach_func apply);
int list_count(struct List *);

#endif
