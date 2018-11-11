#include "../lib/tlpi_hdr.h"

int main(int argc, char** argv) {

    printf("hello world from printf");

    write(STDOUT_FILENO,"hello world from write",50);

    fork();

    exit(EXIT_SUCCESS);
//    return 0;
}