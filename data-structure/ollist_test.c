#include "ollist.h"

int
compare(const void *arg1, const void *arg2)
{
	return strcmp((char *)arg1, (char *)arg2);
}

void
print(const void *arg)
{
	printf("%s\n", (char *)arg);
}

int
main(int argc, char **argv)
{
	struct OLList *ol = create_ollist(compare, NULL);

	ollist_insert(ol, "HelloWorld"); 
	ollist_insert(ol, "Wonderful"); 
	ollist_insert(ol, "Ubuntu Linux"); 
	ollist_insert(ol, "GNU Object"); 

	ollist_foreach(ol, print);
	printf("\nCount: %d\n", ollist_count(ol));

	destroy_ollist(ol, FALSE);
}
