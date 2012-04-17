#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node *merge(struct Node *, struct Node *);
struct Node *merge_sort(struct Node *);

struct Node {
	struct Node *next;
	int value;
};

struct Node *
merge_sort(struct Node *head)
{
	struct Node *fast, *slow;
	fast = slow = head;

	if(fast==NULL || fast->next==NULL)
		return fast;

	/* a tricky way to separate the linked list to two parts */
	while(fast->next!=NULL && fast->next->next!=NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}

	fast = slow->next;
	slow->next = NULL;
	slow = head;

	return merge(merge_sort(slow), merge_sort(fast));
}

struct Node *
merge(struct Node *first, struct Node *second)
{
	if(first == NULL)
		return second;
	if(second == NULL)
		return first;

	struct Node *tmp;
	if(first->value < second->value) {
		tmp = first;
		tmp->next = merge(first->next, second);
	} else {
		tmp = second;
		tmp->next = merge(first, second->next);
	}
	return tmp;
}

/* FOR TEST ONLY */
void
print(struct Node *head)
{
	while(head != NULL) {
		printf("%d\t", head->value);
		head = head->next;
	}
	printf("\n");
}

int
main(int argc, char **argv)
{
	struct Node a, b, c, d, e, f, g;
	a.value = 5;
	b.value = 11;
	c.value = 2;
	d.value = 88;
	e.value = 7;
	f.value = 35;
	g.value = 0;

	a.next = &b;
	b.next = &c;
	c.next = &d;
	d.next = &e;
	e.next = &f;
	f.next = &g;
	g.next = NULL;

	print(&a);
	struct Node *rt = merge_sort(&a);
	print(rt);

	return 0;
}
