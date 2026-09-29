#include <stdio.h>

typedef union {
    int integer_value;
    struct {
        unsigned char version : 4;
        unsigned char ihl : 4;
        unsigned char dscp : 6;
        unsigned char ecn : 2;
        unsigned short total_length : 16;
    } h1;
} packet;

int main () {
    packet P1;
    scanf("%d", &P1);
    printf("Version is %u\n", P1.h1.version);
    printf("IHL is %u\n", P1.h1.ihl);
    printf("DSCP is %u\n", P1.h1.dscp);
    printf("ECN is %u\n", P1.h1.ecn);
    printf("Total length is %u\n", P1.h1.total_length);
    printf("Size is %u", sizeof(P1));
    return 0;
}