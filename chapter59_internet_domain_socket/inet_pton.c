#include <arpa/inet.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char **argv) {
    struct in_addr addr;
    if (inet_pton(AF_INET, "120.77.220.239", &addr) != 1)
        errExit("error inet_pton");

    printf("%llu\n", (unsigned long long) addr.s_addr);
    return 0;
}