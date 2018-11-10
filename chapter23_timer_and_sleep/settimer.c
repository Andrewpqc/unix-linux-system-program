#include "../lib/tlpi_hdr.h"
#include <sys/time.h>
#include <signal.h>

void sigalarm_handler(int sig) {
    printf("timer expires\n");
//    err_exit("");
}

int main(int argc, char** argv) {

    if(signal(SIGALRM,sigalarm_handler)==SIG_ERR) errExit("error signal");

    struct itimerval new_value;

    /* 当两者全为0的时候，为一次性定时器
     * 当两者有一个不为0时，为周期性定时器 */
    new_value.it_interval.tv_sec=1;
    new_value.it_interval.tv_usec=0;

    //1秒种之后超时
    new_value.it_value.tv_sec=1;
    new_value.it_value.tv_usec=0;

    //到期后产生SIGALARM信号
    if(setitimer(ITIMER_REAL,&new_value,NULL)==-1) errExit("error setitimer");

    while(1);

    return 0;
}