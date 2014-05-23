/*
 * Problem:
 * given two ordered list: head1 and head2, merge them in order
 *
 * Key-Points:
 * refer to merge function in merge-sort
 *
 * Date:
 * 05-17-2010
 */

#include<stdio.h>
typedef int Element;
struct ListNode {
	Element element;
	struct ListNode *next;
};

struct ListNode *
merge_list(struct ListNode *head1, struct ListNode *head2)
{
	struct ListNode *mhead, *last = NULL;
	if(head1 == NULL)
		return head2;
	if(head2 == NULL)
		return head1;
	if(head1->element < head2->element) {
		mhead = last = head1;
		head1 = head1->next;
	} else {
		mhead = last = head2;
		head2 = head2->next;
	}
	while(head1 != NULL && head2 != NULL) {
		if(head1->element < head2->element) {
			last->next = head1;
			last = head1;
			head1 = head1->next;
		} else {
			last->next = head2;
			last = head2;
			head2 = head2->next;
		}
	}
	if(head1 == NULL)
		last->next = head2;
	if(head2 == NULL)
		last->next = head1;

	return mhead;
}

struct ListNode *
merge_list_recursive(struct ListNode *head1, struct ListNode *head2)
{
	struct ListNode *mhead;
	if(head1 == NULL)
		return head2;
	if(head2 == NULL)
		return head1;
	if(head1->element < head2->element) {
		mhead = head1;
		mhead->next = merge_list_recursive(head1->next, head2);
	} else {
		mhead = head2;
		mhead->next = merge_list_recursive(head1, head2->next);
	}
	return mhead;
}

/* -------------------test-------------------------- */
void
print_list(struct ListNode *list)
{
	while(list != NULL) {
		printf("%d\t", list->element);
		list = list->next;
	}
	printf("\n");
}

int
main(int argc, char **argv)
{
	struct ListNode a, b, c, d, e;
	a.element = 1;
	a.next = &b;
	b.element = 5;
	b.next = &c;
	c.element = 10;
	c.next = NULL;

	d.element = 3;
	d.next = &e;
	e.element = 8;
	e.next = NULL;

	struct ListNode *r;
	print_list(&a);
	print_list(&d);
	print_list(merge_list_recursive(&a, &d));
}
