#include <signal.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char **argv) {

    static size_t process_count = 0;
    for (pid_t i = 1; i < 50000; ++i) {
        ssize_t res = kill(i, 0);
        if (res == 0) {
            printf("process %d exist, have right to send signal\n", i);
            ++process_count;
        } else if (res == -1) {
            if (errno == EPERM) {
                printf("process %d exist, no right to send signal\n", i);
                ++process_count;
            } else if (errno == ESRCH) {
//                printf("process %d not exist.\n",i);
            }
        }
    }

    printf("%lu process in the system\n", process_count);
    return 0;
}