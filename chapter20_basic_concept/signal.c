#include <signal.h>
#include "../lib/tlpi_hdr.h"

/* 为信号处理器函数取个别名 */
//typedef void (*sighandler_t)(int);

/* print some message and exit */
void sigint_handler(int sig) {
    printf("handler of sigint\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv) {
    /* register sigint_handler to handle SIGINT*/
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        errExit("error handle sigint");
    }

    /* to take the default action when SIGINT is coming */
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        errExit("error");
    }

    /* to ignore SIGCHLD*/
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
        errExit("error");
    }

    while (1);

    return 0;
}