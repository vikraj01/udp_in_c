#include "udp_common.h"

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    bind_socket(skfd, &serv_addr);

    char buf[BUF_SIZE];
    socklen_t addrlen = sizeof(cli_addr);
    int len;

    while (1)
    {
        printf("Server: Listening for client\n");
        len = recv_msg(skfd, buf, &cli_addr, &addrlen);
        printf("\nReceived message from client: %s\n", buf);
        printf("Enter Message Send To Client : ");
        send_msg(skfd, buf, &cli_addr, addrlen);
        buf[0] = '\0';
    }

    close(skfd);
    return 0;
}
