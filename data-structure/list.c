#include "list.h"

struct List {
	struct Node *head, *tail;
	int count;
	release_func release;
};

struct List *
create_list(release_func rel)
{
	struct List *list = (struct List *)malloc(sizeof(struct List));
	if(list != NULL) {
		list->head = list->tail = NULL;
		list->count = 0;
		list->release = rel;
	}
	return list;
}

void
destroy_list(struct List *list, BOOL mem_release)
{
	if(list != NULL) {
		struct Node *tmp, *ptr = list->head;
		while(ptr != NULL) {
			tmp = ptr;
			ptr = ptr->next;

			if(list->release && mem_release)
				list->release(tmp->val);
			free(tmp);
		}
		free(list);
	}
}

BOOL
list_push_back(struct List *list, void *data)
{
	assert(list != NULL);

	if(data == NULL)
		return FALSE;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if(node == NULL)
		return FALSE;
	node->val = data;
	node->pre = node->next = NULL;

	if(list->count == 0)
		list->head = list->tail = node;
	else {
		list->tail->next = node;
		node->pre = list->tail;

		list->tail = node;
	}

	++(list->count);
	return TRUE;
}

BOOL
list_push_front(struct List *list, void *data)
{
	assert(list != NULL);

	if(data == NULL)
		return FALSE;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if(node == NULL)
		return FALSE;
	node->val = data;
	node->pre = node->next = NULL;

	if(list->count == 0)
		list->head = list->tail = node;
	else {
		list->head->pre = node;
		node->next = list->head;

		list->head = node;
	}

	++(list->count);
	return TRUE;
}

BOOL
list_insert_after(struct List *list, struct Node *target, void *data)
{
	assert(list!=NULL && target!=NULL);

	if(data == NULL)
		return FALSE;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if(node == NULL)
		return FALSE;
	node->val = data;
	
	node->next = target->next;
	if(target->next)
		target->next->pre = node;
	else /* target == list->tail */
		list->tail = node;
	target->next = node;
	node->pre = target;

	++(list->count);
	return TRUE;
}

BOOL
list_insert_before(struct List *list, struct Node *target, void *data)
{
	assert(list!=NULL && target!=NULL);

	if(data == NULL)
		return FALSE;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if(node == NULL)
		return FALSE;
	node->val = data;

	node->pre = target->pre;
	if(target->pre)
		target->pre->next = node;
	else /* target == list->head */
		list->head = node;
	target->pre = node;
	node->next = target;

	++(list->count);
	return TRUE;
}

BOOL
list_remove_node(struct List *list, struct Node *target, BOOL mem_release)
{
	assert(list != NULL);

	if(target == NULL)
		return FALSE;

	if(target->pre)
		target->pre->next = target->next;
	if(target->next)
		target->next->pre = target->pre;
	if(target == list->head)
		list->head = target->next;
	if(target == list->tail)
		list->tail = target->pre;

	if(list->release && mem_release)
		list->release(target->val);
	free(target);

	--(list->count);

	return TRUE;
}

BOOL
list_remove(struct List *list, void *data, compare_func compare, BOOL mem_release)
{
	struct Node *node = list_find(list, data, compare);
	return list_remove_node(list, node, mem_release);
}

struct Node *
list_find(struct List *list, const void *data, compare_func compare)
{
	assert(list!=NULL && compare!=NULL);

	if(data == NULL)
		return NULL;

	struct Node *ptr = list->head;
	while(ptr) {
		if(compare(ptr->val, data) == 0)
			return ptr;

		ptr = ptr->next;
	}
	return NULL;
}

struct Node *
list_head(struct List *list)
{
	assert(list != NULL);
	return (list->head);
}

struct Node *
list_tail(struct List *list)
{
	assert(list != NULL);
	return (list->tail);
}

int
list_count(struct List *list)
{
	assert(list != NULL);
	return (list->count);
}

void
list_foreach(struct List *list, foreach_func apply)
{
	assert(list != NULL);

	if(apply) {
		struct Node *ptr = list->head;
		while(ptr) {
			apply(ptr->val);
			ptr = ptr->next;
		}
	}
}

void
list_foreach_back(struct List *list, foreach_func apply)
{
	assert(list != NULL);

	if(apply) {
		struct Node *ptr = list->tail;
		while(ptr) {
			apply(ptr->val);
			ptr = ptr->pre;
		}
	}
}
