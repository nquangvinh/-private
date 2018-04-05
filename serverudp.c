#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
/* Variable*/
    int sockudp;
    struct sockaddr_in server, client;
    char *buff = (char*) malloc(sizeof(char*));
    int recv;

/* Create socket*/
    sockudp =  socket(AF_INET, SOCK_DGRAM, 0);
    if (sockudp < 0)
    {
        perror("FAIled to create socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(12345);

/* CALL bind*/
    if (bind(sockudp, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind FAILed");
        exit(1);
    }

    do {
            memset((char *)&server, 0, sizeof(server));
            /* wrrite and read with socket*/
            if (recv == recvfrom(sockudp, buff, 1024, 0, &client, sizeof(client)) < 0 )
                perror("reading stream message error");
            else{
                    printf("Got a message :%s\n\n", buff);
                }
    } while (1);
    free(buff);
    shutdown(sockudp, 2);
    close(sockudp);
    return 0;
}