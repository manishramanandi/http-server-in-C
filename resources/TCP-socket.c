// TCP socket server-side code

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <string.h>

// macro difinition
#define PORT 8080

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "HTTp/1.1 200 ok\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    // Use IPv4. Accept connections from any IP address. 
    // Listen on port 8080 (in the right format)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    {
            perror("In bind");
            exit(EXIT_FAILURE);
    }

        if (listen(server_fd, 10) < 0)
        {
            perror("In listen");
            exit(EXIT_FAILURE);
        }
        while(1)
        {
            printf("\n++++++ waiting for new connection +++++++\n\n");
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("In accept");
                    exit(EXIT_FAILURE);
            }

            char buffer[30000] = {0};
                valread = read( new_socket, buffer,30000);


            printf("%s\n",buffer);
            write(new_socket, hello, strlen(hello));
            printf("---------------------Hello message sent------------------\n");;
            close(new_socket);

        }
        return 0;
    }

