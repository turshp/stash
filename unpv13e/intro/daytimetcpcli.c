#include "unp.h"

int main(int argc, char* argv[]) {
    int sockfd, n;
    char readbuf[MAXLINE + 1];
    struct sockaddr_in server_addr;

    if(argc != 2) {
        err_quit("Usage: a.out <IP address>");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13); // daytime
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        err_quit("Invalid IP address");
    }

    Connect(sockfd, (SA *) &server_addr, sizeof(server_addr));
    while ((n = read(sockfd, readbuf, MAXLINE)) > 0) {
        readbuf[n] = 0;
        if (fputs(readbuf, stdout) == EOF) {
            err_sys("fputs error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    return 0;
}
