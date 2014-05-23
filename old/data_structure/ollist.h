#ifndef __OLLIST_H
#define __OLLIST_H

/* 
 * implementation of ordered linked list 
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
	struct Node *next;
};

struct OLList;

struct OLList *create_ollist(compare_func comp, release_func rel);
void destroy_ollist(struct OLList *, BOOL mem_release);

BOOL ollist_insert(struct OLList *, void *value);
BOOL ollist_remove(struct OLList *, void *value, BOOL mem_release);

void ollist_foreach(struct OLList *, foreach_func apply);
int ollist_count(struct OLList *);

#endif
