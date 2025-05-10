#include "error.h"
#include <string.h>
#include <unistd.h>

void send_404(int client_fd) {
    const char *msg = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
    write(client_fd, msg, strlen(msg));
}