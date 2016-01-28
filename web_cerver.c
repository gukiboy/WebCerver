#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{

    int status;
    int socket_desc; // socket file descriptor
    struct addrinfo hints;
    struct addrinfo *servinfo; //points results of addresses

    memset(&hints, 0, sizeof hints); // make sure the structs is empty
    hints.ai_family = AF_UNSPEC;     // does not matter if IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP Stream socket
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if((status = getaddrinfo(NULL,"3490",&hints,&servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    else
    {

        int bind_status;

        socket_desc = socket(servinfo->ai_family ,servinfo->ai_socktype, servinfo->ai_protocol); //initialize socket
        if(bind_status = bind(socket_desc,
                              servinfo->ai_addr,
                              servinfo->ai_addrlen) != 0 ) // binds socket to port from servinfo
        {
            printf("Binding error\n");
            exit(1);
        }
        printf("\nServer is up!\n");
        while(true)
        {

        }
    }

    printf("\nServer is down! :(\n");
    freeaddrinfo(servinfo);
}
