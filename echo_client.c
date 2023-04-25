#include "udp_common.h"

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);

    char buf[BUF_SIZE] = "Why do UDP jokes always get lost? Because the person telling the joke doesn't care if you got it or not.";
    socklen_t addrlen = sizeof(serv_addr);
    int len;

    
    send_msg(skfd, buf, &serv_addr, addrlen);
    len = recv_msg(skfd, buf, &serv_addr, &addrlen);
    printf("Received message from server: %s\n", buf);
    
    close(skfd);
    return 0;
}
