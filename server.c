#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    /* declare */
    int rc = 0;
    struct sockaddr_in bind_addr;
    int tcp_socket = 0;
    int ret = 0;
    int client_socket = 0;

    /* intialize */
    memset(&bind_addr, 0, sizeof(bind_addr));
    tcp_socket = socket(
        AF_INET, /* IPv4 use AF_INET6 for IPv6*/
        SOCK_STREAM, /* TCP */
        0
    );


    if (tcp_socket == -1){
        perror("socket()");
        return 1;
    }
    printf("Socket creation succesfull\n");

    bind_addr.sin_port = htons(6969);
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = INADDR_ANY;

    rc = bind(tcp_socket, (const struct sockaddr*)&bind_addr, sizeof(bind_addr));
    if (rc < 0) {
        perror("bind()");
        ret = 1;
        goto exit;
    }
    printf("bind succesfull\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        ret = 1;
        goto exit;
    }
    printf("listen succesfull\n");
    printf("Suckless code\n");

    for (;;){
    printf("waiting for connection\n");
    client_socket = accept(tcp_socket, NULL, NULL);
    printf("got a connection\n");

    };

exit:
    close(tcp_socket);
    return ret;
}
