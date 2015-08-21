#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


static int
lock_pidfile__(FILE *file, int command, struct flock *lck)
{
    int error;

    lck->l_type = F_WRLCK;
    lck->l_whence = SEEK_SET;
    lck->l_start = 0;
    lck->l_len = 0;
    lck->l_pid = 0;

    do {
        error = fcntl(fileno(file), command, lck) == -1 ? errno : 0;
    } while (error == EINTR);
    return error;
}

static int
lock_pidfile(FILE *file, int command)
{
    struct flock lck;

    return lock_pidfile__(file, command, &lck);
}


const char* pidfile = "/usr/local/var/run/openvswitch/ovsdb-server.pid";

int main() {
    FILE* file;
    struct flock lck;
    int error;


    file = fopen(pidfile, "r+");
    if (!file) {
        printf("%s: open: %s\n", pidfile, strerror(errno));
        exit(-1);
    }

    error = lock_pidfile__(file, F_GETLK, &lck);
    if (error) {
        printf("%s: fcntl: %s\n", pidfile, strerror(error));
        exit(-1);
    }

    if (lck.l_type == F_UNLCK) {
        printf("%s: F_UNLCK\n", pidfile);
    } else if (lck.l_type == F_WRLCK) {
        printf("%s: F_WRLCK\n", pidfile);
    } else {
        printf("%s: F_RDLCK\n", pidfile);
    }

    return 0;
}
