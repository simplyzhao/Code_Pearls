/*
 * Problem:
 * given a list, reverse it.
 */
#include<stdio.h>
typedef int Element;
struct ListNode {
	Element elem;
	struct ListNode *next;
};

struct ListNode *
list_reverse(struct ListNode *head)
{
	struct ListNode *forward, *last, *temp;
	forward = head;
	last = NULL;
	while(forward != NULL) {
		temp = forward->next;
		forward->next = last;
		last = forward;
		forward = temp;
	}
	return last;
}

/* -----------------test--------------------------*/
void 
print_list(struct ListNode *lst)
{
	struct ListNode *t = lst;
	for( ; t!=NULL; t=t->next)
		printf("%d\t", t->elem);
	printf("\n");
}

int
main(int argc, char **argv)
{
	struct ListNode a, b, c, d;
	a.elem = 1;
	a.next = &b;
	b.elem = 2;
	b.next = &c;
	c.elem = 3;
	c.next = &d;
	d.elem = 4;
	d.next = NULL;
	print_list(&a);
	print_list(list_reverse(&a));
}

