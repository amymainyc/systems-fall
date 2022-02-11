#include <stdio.h>

int main() {
    char c = 'w';
    int i = 17;
    long l =  9223372036854775807;

    printf("char hex: %p\nchar decimal: %lu\nint hex: %p\nint decimal: %lu\nlong hex: %p\nlong decimal: %lu\n\n",  &c, &c, &i, &i, &l, &l);

    char *cp = &c;
    int *ip = &i;
    long *lp = &l;

    printf("char: %p\nint: %p\nlong: %p\n\n",  c, i, l);

    unsigned int ui = 2147;
    unsigned int *uiip = &ui;
    char *uicp = &ui;

    printf("uiip: %p \t uiip points to: %u \n", uiip, *uiip);
    printf("uicp: %p \t uicp points to: %u \n\n", uicp, *uicp);

    printf("unsigned int decimal: %u\nunsigned int hex: %x \n\n", ui, ui);

    printf("bytes:\n%hhu\n%hhu\n%hhu\n%hhu\n\n", *((char *)uiip + 0), *((char *)uiip + 1), *((char *)uiip + 2), *((char *)uiip + 3));

    *((char *)uiip + 0) += 1;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 1) += 1;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 2) += 1;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 3) += 1;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n\n", ui, ui);

    printf("+1 incremented bytes:\n%hhu\n%hhu\n%hhu\n%hhu\n\n", *((char *)uiip + 0), *((char *)uiip + 1), *((char *)uiip + 2), *((char *)uiip + 3));

    *((char *)uiip + 0) += 16;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 1) += 16;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 2) += 16;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n", ui, ui);
    *((char *)uiip + 3) += 16;
    printf("unsigned int decimal: %u\nunsigned int hex: %x\n\n", ui, ui);

    printf("+16 incremented bytes:\n%hhu\n%hhu\n%hhu\n%hhu\n\n", *((char *)uiip + 0), *((char *)uiip + 1), *((char *)uiip + 2), *((char *)uiip + 3));
    
}