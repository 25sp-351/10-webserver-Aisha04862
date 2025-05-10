#ifndef WEB_ROUTES_H
#define WEB_ROUTES_H

void handle_static(int client_fd, const char *filepath);
void handle_calc(int client_fd, const char *operation_path);

#endif