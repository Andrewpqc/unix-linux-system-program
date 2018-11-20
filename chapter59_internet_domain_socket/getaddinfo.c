#include <sys/socket.h>
#include <netdb.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char** argv) {
    struct addrinfo addrinfo_hints, *addrinfo_result;

    // addrinfo_hints指定如何获取addrinfo_result
    addrinfo_hints.ai_family=AF_UNSPEC;
    addrinfo_hints.ai_socktype=SOCK_STREAM;
    addrinfo_hints.ai_protocol=0;
    addrinfo_hints.ai_flags |=AI_ADDRCONFIG;
    if(getaddrinfo("tupu.andrewpqc.xyz","http",&addrinfo_hints,&addrinfo_result)!=0){
        errExit("getaddrinfo");
    }

    printf("ip: %s\nport:%s\n",
            addrinfo_result->ai_addr->sa_data,
            addrinfo_result->ai_canonname);

    return 0;
}