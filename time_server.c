#include "udp_common.h"
#include <time.h>

int main() 
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);

    char buff[128];
    socklen_t cli_struct_len = sizeof(cli_addr);
    time_t ticks;
    struct tm gtime;

    for (;;) {
        printf("Server: Listening for client, press Ctrl+C to stop\n");

        bzero(&buff, sizeof(buff));
        ticks = time(NULL);
        gmtime_r(&ticks, &gtime);
        asctime_r(&gtime, buff);
        
        sendto(skfd, buff, sizeof(buff), 0, (struct sockaddr *)&cli_addr, cli_struct_len);

        printf("Server: %s", buff);
        
        bzero(buff, 128);
        int r = recv_msg(skfd, buff, &cli_addr, &cli_struct_len);
        printf("%s", buff);
        
        char *hour_str = strstr(buff, ":") + 1;
        float hour = atof(hour_str);
        
        if (hour > 0 && hour < 12) {
            printf("Morning\n");
        } else if (hour >= 12 && hour < 17) {
            printf("Afternoon\n");
        } else if (hour >= 17 && hour < 22) {
            printf("Evening\n");
        } else {
            printf("Night\n");
        }
    }
    
    close(skfd);
    return 0;
}
