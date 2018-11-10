#include "../lib/tlpi_hdr.h"
#include <signal.h>

void sigint_handler(int sig, siginfo_t *siginfo, void *ucontext) {
    printf("si_signo: %d\n", siginfo->si_signo);
    printf("si_code: %d\n", siginfo->si_code);
    printf("pad0: %d\n", siginfo->__pad0);
    errExit("");
}

//OUTPUT

//si_signo: 2
//si_code: 128
//pad0: 0

int main(void) {
    struct sigaction sigaction1;
    sigaction1.sa_flags = SA_SIGINFO;
    sigemptyset(&sigaction1.sa_mask);
    sigaction1.sa_sigaction = sigint_handler;

    if (sigaction(SIGINT, &sigaction1, NULL) == -1)
        errExit("sigaction");

    for (int i = 0;; ++i) {
        printf("%d\n", i);
    }

    return 0;
}