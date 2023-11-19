#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd, port, bytes_sent, bytes_received;
    struct sockaddr_in server;
    char input_buffer[MAX_BUFFER_SIZE];
    char output_buffer[MAX_BUFFER_SIZE];
    pid_t pid, ppid;

  
    printf("Enter server port number: ");
    scanf("%d", &port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        handle_error("Socket creation error");
    }
    printf("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        handle_error("Connection error");
    }
    printf("Connected to the server.\n");

    pid = fork();
    if (pid < 0) {
        handle_error("Fork failed");
    } else if (pid == 0) {
        // Child process (Receiver)
        ppid = getppid();
        printf("Child PID: %d, PPID: %d\n", getpid(), ppid);

        while (1) {
            // Receive a message from the server
            bytes_received = recv(sockfd, input_buffer, sizeof(input_buffer), 0);
            if (bytes_received <= 0) {
                handle_error("Message Receiving Failed");
            }

            input_buffer[bytes_received] = '\0';

            if (strcmp(input_buffer, "BYE") == 0) {
                // Gracefully exit the child process
                break;
            }

            printf("Server: %s\n", input_buffer);
        }
    } else {
        // Parent process (Sender)
        printf("Parent PID: %d\n", getpid());

        while (1) {
            printf("Enter a message (or 'BYE' to exit): ");
            scanf("%s", output_buffer);

            // Send the message to the server
            bytes_sent = send(sockfd, output_buffer, strlen(output_buffer), 0);
            if (bytes_sent == -1) {
                handle_error("Message Sending Failed");
            }

            if (strcmp(output_buffer, "BYE") == 0) {
                // Gracefully exit the parent process
                break;
            }
        }
    }

    close(sockfd);
    printf("Connection closed.\n");

    return 0;
}


