#include "unp.h"
#include <time.h>

int main() {
    int listenfd, connfd;
    char buffer[MAXLINE + 1];
    struct sockaddr_in servaddr;
    time_t ticks;
    int nbytes = 0;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    Bind(listenfd, (SA*)(&servaddr), sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    for(;;) {
        connfd = Accept(listenfd, (SA *)NULL, NULL);
        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));

        nbytes = strlen(buffer);
        if (write(connfd, buffer, nbytes) != nbytes) {
            err_sys("write error");
        }
        if (close(connfd) == -1) {
            err_sys("close error");
        }
    }
}
