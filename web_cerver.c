#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define PORT_NUMBER "3490"

int main()
{

    int status;
    int socket_srv; // socket file descriptor
    int socket_cli; // received socket connection accepted
    struct addrinfo hints;
    struct addrinfo *servinfo; //points results of addresses
    struct sockaddr_storage incoming_addr; // incoming connection

    memset(&hints, 0, sizeof hints); // make sure the structs is empty
    hints.ai_family = AF_UNSPEC;     // does not matter if IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP Stream socket
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if((status = getaddrinfo(NULL,PORT_NUMBER ,&hints,&servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    else
    {

        socket_srv = socket(servinfo->ai_family ,servinfo->ai_socktype, servinfo->ai_protocol); //initialize socket
        if(status = bind(socket_srv,
                              servinfo->ai_addr,
                              servinfo->ai_addrlen) != 0 ) // binds socket to port from servinfo
        {
            printf("Binding error!\n");
            exit(EXIT_FAILURE);
        }

        if((status = listen(socket_srv,10) != 0)) // Starts listening to receiveing  connections
        {
            printf("Listening error!\n");
            exit(EXIT_FAILURE);
        }

        printf("\nServer is up!\n");

        socklen_t addr_size = sizeof incoming_addr;
        if((socket_cli = accept(socket_srv, (struct sockaddr *)&incoming_addr, &addr_size)) == -1)
        {
            printf("Accepting connection error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Someone connected\n");
            char *send_msg = "WELCOME TO IX COLLECTIONS\n";

            char *recv_msg = (char*)malloc(sizeof(char)*500); 
            int len, bytes_sent;
            len = strlen(send_msg);

            bytes_sent = send(socket_cli,send_msg,len,0);

            while((status = recv(socket_cli,recv_msg,sizeof(char)*500,0)) >= 0)
            {
                send_msg = recv_msg;
                len = status;
                send_msg[len]='\0';
                send(socket_cli, send_msg, len, 0);
                send(socket_cli, "RETORNO\0",7,0);
                printf("length %d\n", len);
                printf("status %d\n", status);

                if(status == 0)
                {
                    printf("ERROR: %s\n", strerror(errno));
                }
            }

            if(status <= -1)
            {
                 printf("Error on receiving message!\n");
                 printf("ERROR: %s\n", strerror(errno));
                 exit(EXIT_FAILURE);
            }
        }
    }

    printf("\nServer is down! :(\n");
    freeaddrinfo(servinfo);
}
