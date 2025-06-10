#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFLEN 1024 /* Buffer length */

int main(int argc, char **argv) {
    int n, yes = 1;
    int sd, new_sd, client_len, port;
    struct sockaddr_in server, client;
    char buf[BUFLEN];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    
    port = atoi(argv[1]);

    /* Create a stream socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    /* Allow reuse of address and port */
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    /* Configure server address struct */
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Bind the socket */
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    /* Listen for client connections */
    if (listen(sd, 5) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is listening on port %d...\n", port);

    while (1) {
        client_len = sizeof(client);
        new_sd = accept(sd, (struct sockaddr *)&client, (socklen_t *)&client_len);
        if (new_sd == -1) {
            perror("Accept failed");
            continue;
        }

        n = read(new_sd, buf, sizeof(buf));
        buf[n] = '\0';
        printf("Message received from client: %s\n", buf);
        write(new_sd, buf, n);
        close(new_sd);
    }

    close(sd);
    return 0;
}
