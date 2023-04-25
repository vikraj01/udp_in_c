#include "udp_common.h"

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);

    char buff[BUF_SIZE];
    socklen_t addrlen = sizeof(serv_addr);
    int len;

    while (1) {
        printf("\nEnter the expression: ");
        fgets(buff, BUF_SIZE, stdin);
        len = strlen(buff);

        send_msg(skfd, buff, &serv_addr, sizeof(serv_addr));

        len = recv_msg(skfd, buff, &cli_addr, (socklen_t *)&len);

        if (len == -1) {
            printf("can't divide by zero\n");
        }
        else {
            printf("Result is %s\n", buff);
        }
    }

    close(skfd);
    return 0;
}
