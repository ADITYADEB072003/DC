#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 6000
#define BUFFER_SIZE 1024

int main() {
    int sock;
    socklen_t addr_len;
    char recv_data[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0, 8);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(sock);
        exit(1);
    }

    printf("UDP Server listening on port %d...\n", SERVER_PORT);
    addr_len = sizeof(client_addr);

    while (1) {
        int bytes_read = recvfrom(sock, recv_data, BUFFER_SIZE, 0,
                                  (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_read > 0) {
            recv_data[bytes_read] = '\0';
            printf("Message from %s:%d - %s\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port), recv_data);
        }
    }

    close(sock);
    return 0;
}
