#include "../lib/tlpi_hdr.h"
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char **argv) {
    /*create a soft link*/
    if (symlink("../lib/ename.c.inc", "ename.c.inc.link") == -1)
        errExit("error symlink");

    /*open the soft link*/
    int fd = open("ename.c.inc.link", O_RDONLY);
    if (fd == -1)errExit("error open");

    puts("following is open the link file\n");

    /* read the content of the soft link file descriptor
     * (with the `read` system call), we can get the
     * content of the source file*/
    char buf[BUF_SIZE];
    ssize_t readNum = 0;
    while ((readNum = read(fd, buf, BUF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, BUF_SIZE) != readNum)
            fatal("can't write whole");
    }
    if (readNum < 0) errExit("error read");

    if (close(fd) == -1) errExit("error close");


    /* the system call `readlink()` can get the content
     * of the link self, and we can found that the content
     * of the soft link file is the filename of the source
     * file*/
    char linkBuf[BUF_SIZE];
    readlink("ename.c.inc.link", linkBuf, BUF_SIZE);
    puts("\n\n\ncontent of the like file\n");
    puts(linkBuf);

    return 0;
}