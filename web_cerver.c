#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{

    int status;
    struct addrinfo hints;
    struct addrinto *servinfo; //points results

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
        printf("\nServer is up!\n");
	while(true)
        {
            
           if(accept()) 
        }

    }

    printf("\nServer is down! :(\n");
    freeaddrinfo(servinfo);
}
