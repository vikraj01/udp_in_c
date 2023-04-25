#include "udp_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 26000

int main(int argc, char *argv[]) {
    int sockfd = create_socket();
    struct sockaddr_in serv_addr;
    init_sockaddr(&serv_addr, SERVER_IP, SERVER_PORT);
    char buffer[BUF_SIZE];
    socklen_t serv_addr_len = sizeof(serv_addr);

    printf("Connected to server.\n");

    // Get the current time
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char *time_string = asctime(time_info);

    // Send the time to the server
    send_msg(sockfd, time_string, &serv_addr, serv_addr_len);
    printf("Sent time to server: %s", time_string);

    // Receive the server's response
    recv_msg(sockfd, buffer, &serv_addr, &serv_addr_len);
    printf("Received message from server: %s", buffer);

    // Extract the hour from the server's response
    char hour_str[3];
    hour_str[0] = buffer[11];
    hour_str[1] = buffer[12];
    hour_str[2] = '\0';
    float hour = atof(hour_str);

    // Determine the appropriate greeting based on the hour
    char *greeting;
    if (hour >= 0 && hour < 12) {
        greeting = "Good morning";
    } else if (hour >= 12 && hour < 17) {
        greeting = "Good afternoon";
    } else if (hour >= 17 && hour < 22) {
        greeting = "Good evening";
    } else if (hour >= 22 && hour <= 24) {
        greeting = "Good night";
    }

    printf("%s!\n", greeting);

    close(sockfd);
    return 0;
}
