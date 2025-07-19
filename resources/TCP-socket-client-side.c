// client side c/c++ program to demostrate socket programg

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[])
{

    int socke = 0; long valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((socke = socket(AF_INET, SOCK_STREAM, 0)) <0 )
    {
        printf("\n Socket creation error \n");
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );
        

    // convert IPv4 and IPv6 addresses from text to binary form
if (inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr) <=0)
    {
        printf("\nInvalid address/ ADdress not supported \n");
        return -1;
    }

if (connect(socke, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection failed \n");
        return  -1;
    }

    send(socke, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read( socke, buffer, 1024);
    printf("%s\n", buffer);
    return 0;


}
