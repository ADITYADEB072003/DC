#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>

#define SERVER_PORT 6000
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"  // IP address of the server

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char send_data[BUFFER_SIZE];

    // Resolve server IP address
 host = gethostbyname(SERVER_IP);
    // if (host == NULL) {
    //     perror("Error resolving host");
    //     exit(1);
    // }

    // // Create UDP socket
   sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }


    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(server_addr.sin_zero), 0, 8);

    // Communication loop
    while (1) {
        printf("Type something (q or Q to quit): ");
        fgets(send_data, BUFFER_SIZE, stdin);
        send_data[strcspn(send_data, "\n")] = '\0';  // Remove newline

        if (strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0) {
            break;
        }

        // Send data to server
        sendto(sock, send_data, strlen(send_data), 0, 
               (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    }

    close(sock);
    return 0;
}
