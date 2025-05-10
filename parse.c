#include "parse.h"
#include "web_routes.h"
#include "error.h"
#include <string.h>
#include <stdio.h>

void dispatch_request(int client_fd, const char *request) {
    if (strncmp(request, "GET ", 4) != 0) {
        send_404(client_fd);
        return;
    }

    const char *path_start = request + 4;
    const char *path_end = strchr(path_start, ' ');
    if (!path_end) {
        send_404(client_fd);
        return;
    }

    char path[256] = {0};
    strncpy(path, path_start, path_end - path_start);

    if (strncmp(path, "/static/", 8) == 0) {
        handle_static(client_fd, path + 8);
    } else if (strncmp(path, "/calc/", 6) == 0) {
        handle_calc(client_fd, path + 6);
    } else {
        send_404(client_fd);
    }
}