#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char template[] = "/tmp/somestringXXXXXX";//必须以XXXXXX结尾
    int temp_fd = mkstemp(template);

    if (temp_fd == -1) perror("mkstemp error");

    //read(),write() ... on temp_fd;


    printf("generated filename is: %s\n", template);

    unlink(template);//程序退出前自动删除临时文件

    char buf[20] = "some contents";
    if (write(temp_fd, buf, 20) == -1) {
        perror("write error");
    }

    sleep(20);

    if (close(temp_fd) == -1) perror("close error"); //tempfile was removed;

    return 0;
}