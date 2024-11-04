  while (1) {
        int bytes_read = recvfrom(sock, recv_data, BUFFER_SIZE, 0,
                                  (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_read > 0) {
            recv_data[bytes_read] = '\0';
            printf("Message from %s:%d - %s\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port), recv_data);
        }
    }