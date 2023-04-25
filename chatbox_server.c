#include "udp_common.h"

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    bind_socket(skfd, &serv_addr);

    char buf[BUF_SIZE];
    socklen_t addrlen = sizeof(cli_addr);
    int len;

    for (;;)
    {
        printf("Server: Listening for client\n");
        while (1)
        {
            len = recv_msg(skfd, buf, &cli_addr, &addrlen);
            printf("\nReceived message from client: %s\n", buf);
            if (!strncmp(buf, "bye", 3)){
                printf("Client left\n");
                break;
            }
            printf("Enter Message Send To Client : ");
            gets(buf);
            send_msg(skfd, buf, &cli_addr, addrlen);
            if(!strncmp(buf,"bye",3))
				die(buf);
            buf[0] = '\0';
        }    }

    close(skfd);
    return 0;
}
