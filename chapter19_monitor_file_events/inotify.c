#include <sys/inotify.h>
#include "../lib/tlpi_hdr.h"
#include <limits.h>

static void displayINotifyEvent(struct inotify_event *ie) {
    printf("wd = %2d\n", ie->wd);
    if (ie->cookie > 0) printf("cookie = %4d\n", ie->cookie);

    printf("mask = ");
    if (ie->mask & IN_ACCESS) printf("IN_ACCESS ");
    if (ie->mask & IN_ATTRIB) printf("IN_ATTRIB ");
    if (ie->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (ie->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE ");
    if (ie->mask & IN_CREATE) printf("IN_CREATE ");
    if (ie->mask & IN_DELETE) printf("IN_DELETE ");
    if (ie->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF ");
    if (ie->mask & IN_IGNORED) printf("IN_IGNORED ");
    if (ie->mask & IN_ISDIR) printf("IN_ISDIR ");
    if (ie->mask & IN_MODIFY) printf("IN_MODIFY ");
    if (ie->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF ");
    if (ie->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM ");
    if (ie->mask & IN_MOVED_TO) printf("IN_MOVED_TO ");
    if (ie->mask & IN_OPEN) printf("IN_OPEN ");
    if (ie->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW ");
    if (ie->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
    printf("\n");

    if (ie->len > 0) printf("name = %s \n\n\n", ie->name);
}

/* read buffer */
const size_t BUF_LEN = (10 * (sizeof(struct inotify_event) + NAME_MAX + 1));


int main(int argc, char **argv) {
    int inotify_fd = inotify_init();
    if (inotify_fd == -1) errExit("error inotify_init");

    for (int i = 1; i < argc; ++i) {
        /* monitor all events of all items */
        int watched_descriptor = inotify_add_watch(inotify_fd, argv[i], IN_ALL_EVENTS);
        if (watched_descriptor == -1) errExit("error inotify_add_watch");

        printf("%s 's watched descriptor is %d\n", argv[i], watched_descriptor);
    }

    char buf[BUF_LEN];
    for (;;) {
        ssize_t numRead = read(inotify_fd, buf, BUF_LEN);
        if (numRead == 0) fatal("read from inotify fd return 0!");

        if (numRead < 0) errExit("error read");

        printf("read %ld bytes from inotify fd\n", numRead);

        for (char *p = buf; p < buf + numRead;) {
            struct inotify_event *event = (struct inotify_event *) p;
            displayINotifyEvent(event);
            p += sizeof(struct inotify_event) + event->len;
        }
    }


    return 0;
}