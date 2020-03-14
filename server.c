#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


int main(int argc, char *argv[]) {
    int sockfd, clientfd;
    struct sockaddr_in saddr;
    unsigned short port = 8784;
    unsigned int clen;
    pthread_t input_thread;

    // create the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    // bind the socket to port
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        printf("Error binding socket\n");
        close(sockfd);
        return -1;
    }

    // then listen
    listen(sockfd, 5);
    clen = sizeof(saddr);


    // wait and accept an incoming connection
    printf("server> accepting incoming connection\n");
    clientfd = accept(sockfd, (struct sockaddr *) &saddr, &clen);

    char buffer[100];

    
    while (1) {
        
        // TODO: communicate with connected client here
        
        bzero(buffer,strlen(buffer));
        recv(clientfd, buffer, sizeof(buffer), 0);
        printf("Messeage from client: %s\n", buffer);

        bzero(buffer,strlen(buffer));
        printf("Server enters message:");
        // scanf("%s", buffer);
        fgets(buffer, sizeof(buffer), stdin);
        send(clientfd, buffer, strlen(buffer), 0);
        

        
    }
    close(clientfd);

}