#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void *func (void *arg);

int sock, c, client_sock, i, listen_sock;

int main(int argc, char const *argv[])
{
/* Variable*/
    struct sockaddr_in server, client;

/* Create socket*/
    sock =  socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    printf("which PORT NUMBER: ");
    int port;
    scanf("%d", &port);
    printf("how many client: ");
    int num_cli;
    scanf("%d", &num_cli);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // or addr.sin_addr.s_addr = inet_addr(server_ip); with char server_ip[] = "127.0.0.1";
    server.sin_port = htons(port);

/* bind socket */
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) { // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        perror("bind Failed");
        exit(1);
    }

/* Listen socket*/
    if (listen_sock = listen(sock, 5) < 0){
    shutdown(sock, 2);
    close(sock);
    exit(1);
    }
    c = sizeof(struct sockaddr_in);
    pthread_t *thread;
    thread = malloc((num_cli)*sizeof(*thread));
/*Accept socket*/
    for (i = 0; i < num_cli; i++) {
        client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);//return addrasss of clinet connecting to socket// soclen_t: size of protocol address
        printf("Connection accepted with Client ID %d\n", client_sock);
        if( pthread_create( &thread[i] , NULL , func , (void*)&client_sock) < 0) {
            perror("could not create thread");
            goto shutdown;
        }
        
        if (client_sock < 0) {
            perror("accept failed");
            goto shutdown;
        }  
    }

/*join pthread*/
    for (i = 0 ; i < num_cli; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("ALL client disconnected -> shutdown\n");
    goto shutdown;
    shutdown:
    {
        thread = NULL;
        free(thread);
        shutdown(sock, 2);
        close(sock);
        return 0;
    }
    return 0;
}

void *func (void *arg) {
    int sock_client = *(int*)arg; 
    int read_size;
    char client_message[1024];

    while( (read_size = recv(sock_client, client_message , 1024, 0)) > 0 ) {
        printf("Receive message: \'%s\' from Client ID %d\n", client_message, sock_client);;
    }

    if(read_size == 0) {
        puts("some client disconnected");
        close(sock_client);
        pthread_exit(NULL);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    return 0;
}