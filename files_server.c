#include "udp_common.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
    int skfd = create_socket();
    init_sockaddr(&serv_addr, "127.0.0.1", 26000);
    bind_socket(skfd, &serv_addr);

    char buf[BUF_SIZE];
    socklen_t addrlen = sizeof(cli_addr);
    int len;

    printf("Server started listening on port 26000.\n");

    while (1) {
        len = recv_msg(skfd, buf, &cli_addr, &addrlen);

        DIR *dir;
        struct dirent *ent;

        if ((dir = opendir(".")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strcmp(ent->d_name, buf) == 0) {
                    // file found
                    char file_buf[BUF_SIZE];
                    FILE *fp = fopen(ent->d_name, "r");
                    if (fp == NULL) {
                        die("fopen() failed");
                    }
                    fread(file_buf, BUF_SIZE, 1, fp);
                    fclose(fp);
                    send_msg(skfd, file_buf, &cli_addr, addrlen);
                    break;
                }
            }
            closedir(dir);
        } else {
            // could not open directory
            die("opendir() failed");
        }

        if (ent == NULL) {
            // file not found
            send_msg(skfd, "File not found.", &cli_addr, addrlen);
        }
        buf[0] = '\0';
    }

    close(skfd);
    return 0;
}
