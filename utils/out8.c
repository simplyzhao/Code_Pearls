/* A generic program to write IO port */
#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>
int main(int argc,char *argv[])
{
    unsigned long addr;
    unsigned long value;
    unsigned char res;

    if (argc < 3) { printf("usage: %s addr value\n--- Writes a byte to IO space\n", argv[0]); return 1;}
    addr = strtoul(argv[1], NULL, 0);
    value = strtoul(argv[2], NULL, 0);
    res = value;

    iopl(3);
    outb(value, addr);
    printf("Wrote 0x%lx to 0x%x\n", value, addr);
    return 0;
}
