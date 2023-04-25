#include "udp_common.h"
#include <stdio.h>

int main() {
    // Create socket and set server address
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    socklen_t addrlen = sizeof(serv_addr);

    while (1) {
        // Get filename from user
        printf("Enter filename: ");
        char filename[BUF_SIZE];
        fgets(filename, BUF_SIZE, stdin);

        // Remove trailing newline character from filename
        filename[strcspn(filename, "\n")] = 0;

        // Send filename to server
        send_msg(skfd, filename, &serv_addr, addrlen);

        // Receive file content or "File not found" message from server
        char buf[BUF_SIZE];
        int len = recv_msg(skfd, buf, &serv_addr, &addrlen);
        printf("%s\n", buf);

        // If "File not found" message received, exit loop
        if (strcmp(buf, "File not found") == 0) {
            break;
        }
    }

    // Close socket and exit
    close(skfd);
    return 0;
}
