#include "../lib/tlpi_hdr.h"
#include <signal.h>

/* 用一个处理器处理两种信号，通过处理器函数的
 * sig参数区分 */
void sigint_or_sigquit_handler(int sig) {
    static int int_count = 0;
    static int quit_count = 0;
    if (sig == SIGINT) {
        ++int_count;
        printf("SIGINT: %d\n", int_count);
    } else if (sig == SIGQUIT) {
        ++quit_count;
        printf("SIGQUIT: %d\n", quit_count);
    } else {
        fatal("error signal type");
    }
}

int main(int argc, char **argv) {
    if (signal(SIGINT, sigint_or_sigquit_handler) == SIG_ERR) {
        errExit("error");
    }

    if (signal(SIGQUIT, sigint_or_sigquit_handler) == SIG_ERR) {
        errExit("error");
    }

    while (1) pause();

    return 0;
}