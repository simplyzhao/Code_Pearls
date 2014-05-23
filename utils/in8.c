/* A generic program to read IO port */
#include <stdio.h>
#include <sys/io.h>

int main(int argc,char *argv[])
{
    long addr;
    unsigned char res;
    int count = 1;

    if (argc < 2) { printf("usage: %s hex-value\n--- Reads a byte from IO space\n", argv[0]); }

    addr = strtoul(argv[1], NULL, 0);

    iopl(3);

    if (argc > 2) { count = strtoul(argv[2], NULL, 0); }

    while (count--) {
        res = inb(addr);
        printf("0x%lx contains 0x%x\n", addr, res);
        addr++;
    }

    return 0;
}
