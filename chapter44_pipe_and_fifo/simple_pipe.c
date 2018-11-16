#include "../lib/tlpi_hdr.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    /* fields[0]读取端，fields[1]写入端 */
    int fields[2];
    if (pipe(fields) != 0) errExit("error pipe");

    switch (fork()) {
        case -1:
            errExit("error  fork");
        case 0:
            /* in child process */
            if (close(fields[1]) == -1) errExit("close 1 field in child error");
            char child_buf[BUFSIZ];
            ssize_t readNum = 0;
            for (;;) {
                readNum = read(fields[0], child_buf, BUFSIZ);
                if (readNum == -1) errExit("error read");
                if (readNum == 0) break;
                if (write(STDOUT_FILENO, child_buf, (size_t) readNum) != readNum)
                    fatal("child - partial/failed write");
            }

//            write(STDOUT_FILENO, "\n", 1);

            if (close(fields[0] == -1)) errExit("close 0 field in child error");
            _exit(EXIT_SUCCESS);
        default:
            /* in parent process */
            if (close(fields[0] == -1)) errExit("close 0 field in parent error");

            char buf[20] = "hello,pipe";
            if (write(fields[1], buf, strlen(buf)) != strlen(buf))
                fatal("parent - partial/failed write");

            if (close(fields[1]) == -1) errExit("close 1 field in parent error");

            wait(NULL); //回收子进程

            exit(EXIT_SUCCESS);
    }

}