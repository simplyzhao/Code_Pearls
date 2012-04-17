#include "list.h"

struct Data {
	char *name;
	float price;
};

void
release_data(void *data)
{
	struct Data *s = (struct Data *)data;
	if(s->name)
		free(s->name);
	free(s);
}

void
print(const void *data)
{
	struct Data *s = (struct Data *)data;
	printf("%s: %f\n", s->name, s->price);
}

int
compare(const void *arg1, const void *arg2)
{
	return strcmp(((struct Data *)arg1)->name, ((struct Data *)arg2)->name);
}

int
main(int argc, char **argv)
{
	struct List *list = create_list(release_data);

	struct Data *d1 = (struct Data *)malloc(sizeof(struct Data));
	d1->name = strdup("HollyWood");
	d1->price = 1899.00;

	struct Data *d2 = (struct Data *)malloc(sizeof(struct Data));
	d2->name = strdup("China");
	d2->price = 1.0;

	struct Data *d3 = (struct Data *)malloc(sizeof(struct Data));
	d3->name = strdup("America");
	d3->price = 123.45;

	struct Data *d4 = (struct Data *)malloc(sizeof(struct Data));
	d4->name = strdup("Australia");
	d4->price = 98.33;

	struct Data *d5 = (struct Data *)malloc(sizeof(struct Data));
	d5->name = strdup("WaaHaHa");
	d5->price = 2.7;

	list_push_back(list, d1);
	list_push_front(list, d2);
	list_push_front(list, d3);

	struct Node *node = list_find(list, d1, compare);
	list_insert_after(list, node, d4);
	
	node = list_find(list, d1, compare);
	list_insert_before(list, node, d5);

	list_foreach(list, print);
	printf("---------------------------------------\n");
	list_foreach_back(list, print);
	printf("---------------------------------------\n");
	printf("Count: %d, Head: %s, Tail: %s\n", list_count(list), ((struct Data *)(list_head(list)->val))->name, ((struct Data *)(list_tail(list)->val))->name);
	printf("---------------------------------------\n");

	list_remove(list, d3, compare, TRUE);
	list_remove_node(list, node, TRUE);
	list_remove(list, d4, compare, TRUE);

	list_foreach(list, print);
	printf("---------------------------------------\n");
	list_foreach_back(list, print);
	printf("---------------------------------------\n");
	printf("Count: %d, Head: %s, Tail: %s\n", list_count(list), ((struct Data *)(list_head(list)->val))->name, ((struct Data *)(list_tail(list)->val))->name);
	printf("---------------------------------------\n");

	destroy_list(list, TRUE);
}
