#include "web_routes.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void handle_static(int client_fd, const char *filepath) {
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "static/%s", filepath);

    int fd = open(fullpath, O_RDONLY);
    if (fd < 0) {
        send_404(client_fd);
        return;
    }

    struct stat st;
    fstat(fd, &st);

    char header[256];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\nContent-Length: %lld\r\nContent-Type: application/octet-stream\r\n\r\n",
             (long long)st.st_size);
    write(client_fd, header, strlen(header));

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        write(client_fd, buffer, bytes);
    }

    close(fd);
}

void handle_calc(int client_fd, const char *operation_path) {
    char op[16];
    int a, b;
    if (sscanf(operation_path, "%15[^/]/%d/%d", op, &a, &b) != 3) {
        send_404(client_fd);
        return;
    }

    char response[128];
    int result;

    if (strcmp(op, "add") == 0) {
        result = a + b;
    } else if (strcmp(op, "mul") == 0) {
        result = a * b;
    } else if (strcmp(op, "div") == 0) {
        if (b == 0) {
            snprintf(response, sizeof(response),
                     "HTTP/1.1 400 Bad Request\r\nContent-Length: 15\r\nContent-Type: text/plain\r\n\r\nDivision by zero");
            write(client_fd, response, strlen(response));
            return;
        }
        result = a / b;
    } else {
        send_404(client_fd);
        return;
    }

    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/plain\r\n\r\n%d",
             snprintf(NULL, 0, "%d", result), result);
    write(client_fd, response, strlen(response));
}