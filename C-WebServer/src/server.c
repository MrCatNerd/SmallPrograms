#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

static char *readfile(const char *path);

int main(int argc, char *argv[]) { // TODO: arg argv for port and ip

    unsigned int port = 8080;                        // default
    unsigned int ip_thingy = inet_addr("127.0.0.1"); // default
    char ip_stringy[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip_thingy, ip_stringy, INET_ADDRSTRLEN);

    if (argc >= 2) {
        port = atoi(argv[1]);
    }
    if (argc >= 3) {
        ip_thingy = inet_addr(argv[2]);
    }

    printf("Running the server\n");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[socket] error: socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr =
        INADDR_ANY; // assign any available IP address on the machine
    // server_addr.sin_addr.s_addr = ip_thingy;

    server_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("[socket] error: bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("[socket] error: listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Listening for connections on %s:%d\n", ip_stringy, port);
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd =
        accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("[socket] error: accept");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    char buffer[BUFFER_SIZE];
    unsigned long bytes_received;

    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';

        char *line = strtok(buffer, "\n");
        const char *method = strtok(line, " ");
        const char *filename = strtok(NULL, " ");
        const char *http_version = strtok(NULL, " ");

        printf("method: %s\nfilename: %s\nhttp_version: %s\n", method, filename,
               http_version);

        char *response = NULL;
        char *data = NULL;

        // short error_message_thingy = 200; // TODO: this
        if (strcmp(method, "GET") == 0) {

            if (filename == NULL || filename[0] == '\0')
                filename = "/website/index.html"; // I still add / because its
                                                  // getting terminated later

            char token_filename[strlen(filename) + 1]; // copy the URI because
                                                       // annoying strtok stuff
            strcpy(token_filename, filename);

            strtok((char *)token_filename, ".");
            const char *filetype = strtok(NULL, ".");

            if (filetype == NULL)
                filetype = "plain";

            printf("filetype: %s\n", filetype);

            data = readfile(filename + 1);

            if (data == NULL || data[0] == '\0') {
                if (data != NULL) // I suck at C
                    free(data);

                data = strdup(
                    "<!DOCTYPE html><html><head><title>Error 404 - Page Not "
                    "Found</title></head><body><h1>404 - Page Not "
                    "Found</h1></body></html>");
            }

            unsigned long content_length =
                strlen(data); // the length of the file / content

            response = malloc(
                content_length +
                256); // I am too dumb to calculate the size of the rest of the
                      // http request so I just added 256 (super safe ik)

            snprintf(response, content_length + 256,
                     "HTTP/1.1 200 OK\nContent-Type: text/%s\nContent-Length: "
                     "%lu\n\n%s",
                     filetype, content_length, data);

        } else if (strcmp(method, "POST") == 0) { // TODO: post
            data = strdup(
                "<!DOCTYPE "
                "html><html><head><title>LMAO</title></head><body><h1>bro "
                "thinks i got budget for POST requests</h1></body></html>");
            response = malloc(strlen(data) + 100);

            snprintf(
                response, strlen(data) + 100,
                "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
                "%lu\n\n%s",
                strlen(data), data);
        } else {
            response = strdup(
                "HTTP/1.1 405 Method Not Allowed\nContent-Length: 0\n\n");
        }

        // send the response
        send(client_fd, response, strlen(response) + 1, 0);

        // clean stuff up
        if (response != NULL)
            free(response);

        if (data != NULL)
            free(data);
    }
    if (bytes_received < 0) {
        perror("[socket] error: recv");
    }

    close(client_fd);
    close(sockfd);

    return EXIT_SUCCESS;
}

char *readfile(const char *path) {
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    unsigned long fileSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(fptr);
        return NULL;
    }

    unsigned long bytesRead = fread(buffer, 1, fileSize, fptr);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file %s\n", path);
        fclose(fptr);
        free(buffer);
        return NULL;
    }

    buffer[bytesRead] = '\0';

    fclose(fptr);
    return buffer;
}
