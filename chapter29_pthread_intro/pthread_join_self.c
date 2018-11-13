#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"


int main(int argc, char **argv) {
    printf("hello, pthread\n");

    //what's the problem here???
    pthread_join(pthread_self(), NULL);

    printf("hhh");

    return 0;
}