#include "udp_common.h"

int main() 
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 28002);
    
    char buff[BUF_SIZE], buff_int[BUF_SIZE], buff_ss[BUF_SIZE];
    FILE* fp1;

    printf("\nUDP echo server\n");

    bind_socket(skfd, &serv_addr);

    socklen_t cli_struct_len = sizeof(cli_addr);

    while(1) {
        printf("SERVER: Listening for client, press ctrl+c to stop\n");
        
        buff_ss[0] = '\0';
        buff[0] = '\0';
        
        int len = recv_msg(skfd, buff, &cli_addr, &cli_struct_len);
        
        if (!strcmp("bye", buff)) {
            printf("\nThe client has left\n");
            break;
        } else {
            printf("\nAll files have been shown\n");
            strcat(buff, ">file.txt");
            system(buff);
            fp1 = fopen("file.txt", "r");
            while(fgets(buff_int, BUF_SIZE, fp1) != NULL) {
                strcat(buff_ss, buff_int);
            }
            send_msg(skfd, buff_ss, &cli_addr, cli_struct_len);
        }
    }
    
    close(skfd);
    return 0;
}
