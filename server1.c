#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];

    // Create server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket error");
        exit(1);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5566);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        exit(1);
    }

    // Listen for connections
    listen(server_sock, 5);
    printf("Listening...\n");

    while (1) {
        socklen_t addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

        // Communication with client
        memset(buffer, 0, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        strcpy(buffer, "HI, THIS IS SERVER. HAVE A GREAT LEARNING DAY!!!");
        send(client_sock, buffer, strlen(buffer), 0);
        printf("Server: %s\n", buffer);

        // Close client socket
        close(client_sock);
        printf("Client disconnected.\n\n");
    }

    // Close server socket (unreachable in this loop but good practice)
    close(server_sock);
    return 0;
}