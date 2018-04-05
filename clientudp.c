#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// #define DATA "hello world of socket"

int main(int argc, char const *argv[])
{
    char *DATA = (char *)malloc(sizeof(char*));
    int sock, i, sendsock;
    struct sockaddr_in client;
    struct hostent *hp;


    do
    {
        // create UDP socket
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0)
        {
            perror("socket failed");
            goto shutdown;
        }
        memset((char *)&client, 0, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(12345);
        printf("DATA send (type \"q\" to quit): ");
        gets(DATA);
        char c = DATA[0];
        if ( c == 113) // first character = "q"-> quit
        {
            goto shutdown;
        }
        hp = gethostbyname ("localhost");
        if (hp == 0)
        {
            perror("gethostbyname failed");
            goto shutdown;
        }
        memcpy(&client.sin_addr, hp->h_addr, hp->h_length);
        sendsock = sendto(sock, DATA, 1024, 0, &client, sizeof(client));
        if ( c == 113) // "q" to quit
        {
            goto shutdown;
        }
            if ( sendsock < 0)
            {
                perror("send failed");
                close(sock);
                exit(1);
            }
            printf("sent \"%s\"\n\n", DATA );
            close(sock);
    }   while (1);

    shutdown:
    free(DATA);
    shutdown(sock, 2);
    close(sock);

    return 0;
}