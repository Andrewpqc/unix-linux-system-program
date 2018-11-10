#include <signal.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char **argv) {
    sigset_t sigset, sigset2;
    if (sigemptyset(&sigset) == -1) errExit("error sigemptyset");

    if (sigaddset(&sigset, SIGINT) == -1) errExit("error sigaddset SIGINT");
    if (sigaddset(&sigset, SIGQUIT) == -1) errExit("error sigaddset SIGQUIT");

    if (sigismember(&sigset, SIGQUIT)) {
        printf("SIGQUIT in sigset\n");
    } else {
        printf("SIGQUIT not in sigset\n");
    }

    if (sigdelset(&sigset, SIGINT) == -1) errExit("error sigdelset SIGINT");


    if (sigfillset(&sigset2) == -1) errExit("error sigfullset");

    if (sigdelset(&sigset2, SIGQUIT) == -1) errExit("error sigdelset");

    return 0;
}