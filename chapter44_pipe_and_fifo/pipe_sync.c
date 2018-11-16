/* 用管道进行父子进程之间的同步 */

#include <unistd.h>
#include <stdlib.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char **argv) {

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s int\n", argv[2]);

    int field[2];
    if (pipe(field) != 0) errExit("error pipe");

    for (int i = 0; i < argc; ++i) {
        switch (fork()) {
            case -1:
                errExit("error fork");
            case 0:
                /* in child process*/
                if (close(field[0]) == -1) errExit("error close field 0 in child");
                sleep(2);
                if (close(field[1]) == -1) errExit("error close field 1 in child");
                _exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    if (close(field[1]) == -1) errExit("error close field 1 in parent");

    char buf[5];
    ssize_t readNum = read(field[0], buf, 5);
    if (readNum != 0) fatal("parent didn't get EOF");
    printf("child processes are complete");

    /* parent can do other things here... */


    return 0;
}