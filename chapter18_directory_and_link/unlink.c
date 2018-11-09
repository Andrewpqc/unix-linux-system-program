#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc, char **argv) {

    if (argc != 2) {
        usageErr("%s filename", argv[0]);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        errExit("open error");
    }

    if (unlink(argv[1]) == -1)
        errExit("error unlink");


    /*write some random content to the unlinked file,
     * not initial here, so some rand content in buf.
     * The filename is unlinked, but the file
     * is not delete from the system, because the file
     * descriptor is opened, after the file descriptor
     * closed, the file will be delete then*/
    char buf[BUF_SIZE];
    for (int i = 0; i < 1000;i++) {
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("error write");
    }

    char cmd[CMD_SIZE];
    snprintf(cmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);

    system(cmd);

    if (close(fd) == -1) errExit("error close");
    printf("closed the file descriptor....\n");

    system(cmd);

    return 0;
}


/*
 Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda2      479152840 22754660 431988788   6% /
closed the file descriptor....
Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda2      479152840 22654660 432088788   5% /

 * */