#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Server IP
#define PORT 8080              // Server port
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    FILE *file;
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Specify server details
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));

    // Open the video file
    file = fopen("video.mp4", "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // Send file contents in chunks
    while (!feof(file)) {
        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read > 0) {
            send(sock, buffer, bytes_read, 0);
        }
    }

    // Send EOF indicator
    send(sock, "EOF", 3, 0);

    // Close file and socket
    fclose(file);
    close(sock);

    return 0;
}