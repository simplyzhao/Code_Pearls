/* A generic program to peek the physical memory relying on /dev/mem and mmap */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define handle_error(msg)   do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define DEV_MEM_FILE        "/dev/mem"
#define BYTES_EACH_LINE     16

long
strtoll_safe(const char *input)
{
    long ret = 0;
    char *endptr = NULL;

    errno = 0; /* To distinguish success/failure after call */
    ret = strtoll(input, &endptr, 0);

    /* Check for various possible errors */
    if (((errno == ERANGE) && (ret == LLONG_MAX || ret == LLONG_MIN)) ||
        ((errno != 0) && (ret == 0)))
    {
        handle_error("strtoll");
    }

    if (*endptr != '\0')
    {
        fprintf(stderr, "strtoll | further characters left after number: %s\n", endptr);
    }

    return ret;
}

int
main(int argc, char **argv)
{
    int fd = -1;
    unsigned char *area = NULL;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <offset> <length>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    long offset = strtoll_safe(argv[1]);
    long length = strtoll_safe(argv[2]);

    if ((fd = open(DEV_MEM_FILE, O_RDONLY)) < 0)
    {
        handle_error("open");
    }

    /* offset must be a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE) */
    long page_size = sysconf(_SC_PAGE_SIZE);
    long offset_aligned = (offset & (~(page_size - 1)));
    long length_aligned = length + (offset - offset_aligned);

    area = mmap(NULL, length_aligned, PROT_READ, MAP_PRIVATE, fd, offset_aligned);
    if (area == MAP_FAILED)
    {
        close(fd);
        handle_error("mmap");
    }

    long index;
    for (index = 0; index < length_aligned; ++index)
    {
        if (index % BYTES_EACH_LINE == 0)
        {
            fprintf(stdout, "%08x: ", (offset_aligned + ((index / BYTES_EACH_LINE) * BYTES_EACH_LINE)));
        }

        fprintf(stdout, "%02x ", area[index]);

        if ((index + 1) % BYTES_EACH_LINE == 0)
        {
            fprintf(stdout, "\n");
        }
    }
    fprintf(stdout, "\n");

    if (munmap(area, length_aligned) < 0)
    {
        close(fd);
        handle_error("munmap");
    }

    close(fd);

    return 0;
}
