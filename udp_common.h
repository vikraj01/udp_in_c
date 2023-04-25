#ifndef UDP_COMMON_H
#define UDP_COMMON_H

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUF_SIZE 256

struct sockaddr_in serv_addr, cli_addr;

void die(char *s) {
    perror(s);
    exit(1);
}

void init_sockaddr(struct sockaddr_in *addr, char *ip, unsigned short port) {
    bzero(addr, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    inet_aton(ip, &(addr->sin_addr));
}

int create_socket() {
    int skfd;
    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        die("socket() failed");
    }
    return skfd;
}

void bind_socket(int skfd, struct sockaddr_in *addr) {
    if (bind(skfd, (struct sockaddr*)addr, sizeof(*addr)) < 0) {
        die("bind() failed");
    }
}

void send_msg(int skfd, char *msg, struct sockaddr_in *addr, socklen_t addrlen) {
    int len = strlen(msg);
    if (sendto(skfd, msg, len, 0, (struct sockaddr*)addr, addrlen) != len) {
        die("sendto() sent a different number of bytes than expected");
    }
}

int recv_msg(int skfd, char *buf, struct sockaddr_in *addr, socklen_t *addrlen) {
    int len;
    if ((len = recvfrom(skfd, buf, BUF_SIZE, 0, (struct sockaddr*)addr, addrlen)) < 0) {
        die("recvfrom() failed");
    }
    buf[len] = '\0';
    return len;
}

#endif /* UDP_COMMON_H */
