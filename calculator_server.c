#include "udp_common.h"
#include <ctype.h>

int main() {

    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    bind_socket(skfd, &serv_addr);

    char buffer[BUF_SIZE];
    socklen_t addrlen = sizeof(cli_addr);
    int len;

    printf("UDP Calculator Server running\n");

    for (;;) {
        // Receive expression from client
        len = recv_msg(skfd, buffer, &cli_addr, &addrlen);
        if (len < 0) {
            printf("recvfrom() failed\n");
            continue;
        }
        printf("%d recieved", len);

        // Parse expression and compute result
        int num1, num2, result;
        char op;
        sscanf(buffer, "%d %c %d", &num1, &op, &num2);
        switch (op) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/': result = num2 == 0 ? -1 : num1 / num2; break;
            default:  result = -1; break;
        }

        // Send result to client
        send_msg(skfd, (char *)&result, &cli_addr, addrlen);
    }

    return 0;
}
