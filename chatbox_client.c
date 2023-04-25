#include "udp_common.h"

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    char buf[BUF_SIZE];
    socklen_t addrlen = sizeof(serv_addr);
    int len;

    printf("Connected to server.\n");
    while (1)
    {
        printf("Enter Message Send To Server : ");
        gets(buf);
        send_msg(skfd, buf, &serv_addr, addrlen);
        if (!strncmp(buf, "bye", 3))
            die(buf);
        len = recv_msg(skfd, buf, &serv_addr, &addrlen);
        printf("Received message from server: %s\n", buf);
        if (!strncmp(buf, "bye", 3))
            die(buf);
        buf[0] = '\0';
    }

    close(skfd);
    return 0;
}
