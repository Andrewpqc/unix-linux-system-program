#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
#include <sys/stat.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char **argv) {
    int inputFd, outputFd, openFlags;
    mode_t filePermission;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    filePermission = S_IRUSR | S_IWUSR
                     | S_IRGRP | S_IWGRP
                     | S_IROTH | S_IWOTH;

    outputFd = open(argv[2], openFlags, filePermission);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, BUF_SIZE) != numRead) {
            fatal("could write whole buffer");
        }
    }

    if (numRead == -1) errExit("read");//读取出错

    if (close(inputFd) == -1) errExit("closing inputFd");//关闭inputFd出错
    if (close(outputFd) == -1) errExit("closing outputFd");//关闭outputFd出错

    return 0;
}