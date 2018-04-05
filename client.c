#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int random_number(int min_num, int max_num);
int main(int argc, char const *argv[])
{
    char message[1024];
    int sock, sendsock;
    struct sockaddr_in server;
    struct hostent *hp;

// create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        goto shutdown;
    }
    printf("Enter the port number: ");
    int port;
    scanf("%d", &port);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    hp = gethostbyname ("localhost");
    if (hp == 0)
    {
        perror("gethostbyname failed");
        goto shutdown;
    }

    memcpy(&server.sin_addr, hp->h_addr, hp->h_length); //gan member addr vao truong sin_addr cua struct sever
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror("connect failed");
        goto shutdown;
    }
    memset(message, 0, 1024);
    while (1)
    {
        printf("Send message \"exit\" to disconnect: ");
        gets(message);
        int cmp = strcmp( message, "exit");
        if (cmp == 0)
        {
            printf("*****Disconnect*****\n");
            goto shutdown;
        }
        sendsock = send(sock, message, 1024, 0);
            if ( sendsock < 0)
            {
                perror("send failed");
                goto shutdown;
            }
    }
    shutdown:
    {
        shutdown(sock, 2);
        close(sock);
        exit(1);
    }
    return 0;
}
