#include "../lib/tlpi_hdr.h"
#include <arpa/inet.h>
#include <netinet/in.h>

/* 将二进制的ip地址转换成点分十进制 */
int main(int argc, char** argv) {
    struct in_addr in_addr1={.s_addr=23562563};
    char result[INET_ADDRSTRLEN];
    if(inet_ntop(AF_INET,(void*)(&in_addr1),result,INET_ADDRSTRLEN)==NULL)
        errExit("error inet_ntop");

    printf("%s\n",result);

    return 0;
}