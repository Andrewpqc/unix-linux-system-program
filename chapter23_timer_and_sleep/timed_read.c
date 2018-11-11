#include <sys/time.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"


void sigalrm_handler(int sig) {
    printf("timer expires\n");
}

int main(int argc, char **argv) {
    char buf[BUFSIZ];

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);

    /* clean SA_RESTART flag to prevent the system call to be restarted */
    sa.sa_flags = 0;

    sa.sa_handler = sigalrm_handler;


    /* register the handler of SIGALRM */
    if (sigaction(SIGALRM, &sa, NULL) == -1) errExit("error sigaction");

    /*set the timer*/
    alarm(5);

    ssize_t read_num = read(STDIN_FILENO, buf, BUFSIZ);

    /*cancel the timer*/
    int errnoSave = errno;
    alarm(0);
    errno = errnoSave;

    if (read_num == -1) {
        if (errno == EINTR) {
            printf("read time out\n");
        } else {
            errExit("error read");
        }
    } else {
        printf("successfully read %ld bytes, that is:", read_num);
        printf("%s", buf);
    }

    return 0;
}

