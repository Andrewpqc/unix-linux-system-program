#define _XOPEN_SOURCE 600

#include <signal.h>
#include <unistd.h>
#include <string.h>
//#include <crypt.h>
#include "../lib/tlpi_hdr.h"

static char *str2;

void sigint_handler(int sig) {
    crypt(str2, "xx");
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s str1 str2\n", argv[0]);

    /* register SIGINT handler with sigaction */
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    str2 = argv[2];
    char *encodedStr1 = strdup(crypt(argv[1], "xx")); // store to encodedStr1

    for (int i = 0;; ++i) {
        if (strcmp(crypt(argv[1], "xx"), encodedStr1) != 0) {
            printf("mismatched\n");
            errExit("mismatched");
        }

        printf("%d\n", i);

    }


    return 0;
}