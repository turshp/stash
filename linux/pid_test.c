#include <stdio.h>
#include "lib/daemon.h"



const char* pidfile = "/usr/local/var/run/openvswitch/ovsdb-server.pid";

int main() {
    pid_t ret = read_pidfile(pidfile);
    printf("read pidfile: %d", ret);
}
