#include "priqueue.h"

int
compare(const void *arg1, const void *arg2)
{
	return strcmp((char *)arg1, (char *)arg2);
}

int
main(int argc, char **argv)
{
	struct PriQueue *priqueue = create_priqueue(0, compare);

	priqueue_insert(priqueue, "Oh, My God");
	priqueue_insert(priqueue, "Open");
	priqueue_insert(priqueue, "StdIO");
	priqueue_insert(priqueue, "EOF");
	priqueue_insert(priqueue, "Algorithm");

	while(!priqueue_is_empty(priqueue)) {
		printf("%s\n", (char *)priqueue_extract(priqueue));
	}

	destroy_priqueue(priqueue);
}
