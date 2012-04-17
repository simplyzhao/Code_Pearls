#include "ollist.h"

struct OLList {
	struct Node *head;
	int count;
	compare_func compare;
	release_func release;
};

struct OLList *
create_ollist(compare_func comp, release_func rel)
{
	assert(comp != NULL);

	struct OLList *ollist = (struct OLList *)malloc(sizeof(struct OLList));
	if(ollist != NULL) {
		ollist->head = NULL;
		ollist->count = 0;
		ollist->compare = comp;
		ollist->release = rel;
	}
	return ollist;
}

void
destroy_ollist(struct OLList *ollist, BOOL mem_release)
{
	if(ollist == NULL)
		return;

	struct Node *ptr, *loop;
	ptr = loop = ollist->head;
	while(loop != NULL) {
		ptr = loop;
		loop = loop->next;
		
		if(ollist->release && mem_release)
			ollist->release(ptr->val);
		free(ptr);
	}
	free(ollist);
}

void
ollist_foreach(struct OLList *ollist, foreach_func apply)
{
	assert(ollist != NULL);

	struct Node *ptr = ollist->head;
	if(apply) {
		while(ptr) {
			apply(ptr->val);
			ptr = ptr->next;
		}
	}
}

BOOL
ollist_insert(struct OLList *ollist, void *value)
{
	assert(ollist != NULL);

	if(value == NULL)
		return FALSE;

	struct Node **pptr = &(ollist->head);
	struct Node *cur = ollist->head;

	while(cur!=NULL && ollist->compare(cur->val, value)<0) {
		pptr = &(cur->next);
		cur = *pptr;
	}

	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if(node == NULL)
		return FALSE;
	node->val = value;
	node->next = cur;
	*pptr = node;
	++(ollist->count);
	return TRUE;
}

BOOL
ollist_remove(struct OLList *ollist, void *value, BOOL mem_release)
{
	assert(ollist != NULL);

	if(value == NULL)
		return FALSE;

	struct Node **pptr = &(ollist->head);
	struct Node *cur = ollist->head;

	while(cur!=NULL && ollist->compare(cur->val, value)!=0) {
		pptr = &(cur->next);
		cur = *pptr;
	}

	if(cur == NULL) /* no such node exists */
		return FALSE;

	*pptr = cur->next;
	if(ollist->release && mem_release)
		ollist->release(cur->val);
	free(cur);
	--(ollist->count);
	return TRUE;
}

int
ollist_count(struct OLList *ollist)
{
	assert(ollist != NULL);
	return (ollist->count);
}
