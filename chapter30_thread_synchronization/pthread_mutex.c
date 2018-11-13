#include <pthread.h>
#include <string.h>
#include "../lib/tlpi_hdr.h"


static long long glob = 0;

/* 静态分配的互斥量 */
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;

//pthread_mutex_t mux2 = pthread_mutex_init();
static void *thread_func(void *argc) {
    long long loop_num = *((long long *) argc);

    for (long long i = 0; i < loop_num; ++i) {
        pthread_mutex_lock(&mux);
        ++glob;
        pthread_mutex_unlock(&mux);

//        pthread_mutex_lock(&mux2);
//        ++glob;
//        pthread_mutex_unlock(&mux2);
    }

    return (void *) 0;
}

int main(int argc, char **argv) {

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num\n", argv[0]);

    long long loop_num = atoll(argv[1]);

    pthread_t tid1, tid2;

    int s1 = pthread_create(&tid1, NULL, thread_func, (void *) (&loop_num));
    if (s1 != 0) errExitEN(s1, "pthread_create");

    int s2 = pthread_create(&tid2, NULL, thread_func, (void *) (&loop_num));
    if (s2 != 0) errExitEN(s2, "pthread_create");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("%lld\n", glob);

    return 0;
}