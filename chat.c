#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SERVER_TCP_PORT 5750  /* Well-known port */
#define BUFLEN 256            /* Buffer length */
#define MAX 90
int flag = 0;
void func(int sockfd) {
    char buff[MAX];
    int n;

    for (;;) {
        if (flag == 1) break;

        bzero(buff, MAX);
        n = read(sockfd, buff, sizeof(buff));
        printf("Message from client: %s", buff);

        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            flag = 1;
            break;
        }
        printf("Enter message to be sent to client: ");
        fgets(buff, sizeof(buff), stdin);
        write(sockfd, buff, strlen(buff));
        bzero(buff, MAX);
    }
}

int main(int argc, char **argv) {
    int sd, new_sd, client_len, port;
    struct sockaddr_in server, client;
    char buff[BUFLEN];
    int yes = 1;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    /* Create a stream socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Can't create a socket\n");
        exit(1);
    }

    /* Allow reuse of address */
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    /* Bind an address to the socket */
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        fprintf(stderr, "Can't bind name to socket\n");
        exit(1);
    }

    /* Queue up to 5 connection requests */
    listen(sd, 5);

    while (1) {
        client_len = sizeof(client);
        if ((new_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1) {
            fprintf(stderr, "Can't accept client\n");
            exit(1);
        }

        func(new_sd);
        close(new_sd);
    }

    close(sd);
    return 0;
}#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFLEN 256  /* Buffer length */
#define MAX 80

void func(int sockfd) {
    char buff[MAX];
    int n;

    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the message to be sent: ");
        fgets(buff, sizeof(buff), stdin);

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }

        write(sockfd, buff, strlen(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("Message from Server: %s", buff);
    }
}

int main(int argc, char **argv) {
    int sd, port;
    struct sockaddr_in server;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    /* Create a stream socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Can't create a socket\n");
        exit(1);
    }

    /* Set up the server address */
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Connect to the server */
    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        fprintf(stderr, "Can't connect\n");
        exit(1);
    }

    func(sd);
    close(sd);
    return 0;
}
