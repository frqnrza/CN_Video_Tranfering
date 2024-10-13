#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // Bind to port
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(server_sock, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for connections
    listen(server_sock, 5);

    // Accept client connection
    client_sock = accept(server_sock, (struct sockaddr*)&client_address, &client_len);

    // Create a new file to save the video
    file = fopen("received_video.mp4", "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // Receive file contents and write to the file
    while (1) {
        ssize_t bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            // Check for EOF signal at the last 3 bytes
            if (bytes_received == 3 && strncmp(buffer, "EOF", 3) == 0) {
                break;
            }
            fwrite(buffer, 1, bytes_received, file);
        }
        else if (bytes_received == 0) {
            // End of transmission
            break;
        }
        else {
            perror("Failed to receive data");
            exit(1);
        }
    }

    // Close file and sockets
    fclose(file);
    close(client_sock);
    close(server_sock);

    return 0;
}
