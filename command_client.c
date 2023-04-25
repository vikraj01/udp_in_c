#include "udp_common.h"

int main() 
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 28002);

    printf("\nUDP command client\n");

    while(1) {
        char cmd[BUF_SIZE];
        printf("\nEnter command to send to server or type 'exit' to quit: ");
        fgets(cmd, BUF_SIZE, stdin);

        // remove newline character from input
        cmd[strcspn(cmd, "\n")] = '\0';

        if (!strcmp("exit", cmd)) {
            printf("\nExiting...\n");
            break;
        } else {
            send_msg(skfd, cmd, &serv_addr, sizeof(serv_addr));

            char resp[BUF_SIZE];
            int len = recv_msg(skfd, resp, &serv_addr, (socklen_t *)sizeof(serv_addr));
            printf("\nServer response: %s\n", resp);
        }
    }

    close(skfd);
    return 0;
}
