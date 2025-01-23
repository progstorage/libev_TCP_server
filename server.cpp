#include <ev.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void log_connection(const std::string& data) {
    std::ofstream log_file("server.log", std::ios::app);
    if (log_file.is_open()) {
        time_t now = time(nullptr);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
        log_file << "[" << time_str << "] " << data << "\n";
        log_file.close();
    } else {
        std::cerr << "Error opening log file!" << std::endl;
    }
}

void read_cb(struct ev_loop* loop, ev_io* watcher, int revents) {
    if (revents & EV_READ) {
        char buffer[BUFFER_SIZE];
        ssize_t received = recv(watcher->fd, buffer, BUFFER_SIZE, 0);

        if (received < 0) {
            std::cerr << "Error receiving data!" << std::endl;
            ev_io_stop(loop, watcher);
            close(watcher->fd);
            delete watcher;
        } else if (received == 0) {
            std::cout << "Client disconnected." << std::endl;
            ev_io_stop(loop, watcher);
            close(watcher->fd);
            delete watcher;
        } else {
            send(watcher->fd, buffer, received, 0);
            std::string data(buffer, received);
            std::cout << "Received data: " << data << std::endl;
            log_connection(data);
        }
    }
}

void accept_cb(struct ev_loop* loop, ev_io* watcher, int revents) {
    if (revents & EV_READ) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(watcher->fd, (sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            std::cerr << "Error accepting client connection!" << std::endl;
            return;
        }

        std::cout << "New connection: " << client_fd << std::endl;

        ev_io* client_watcher = new ev_io;
        ev_io_init(client_watcher, read_cb, client_fd, EV_READ);
        ev_io_start(loop, client_watcher);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error creating socket!" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket!" << std::endl;
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) < 0) {
        std::cerr << "Error listening on port!" << std::endl;
        return 1;
    }

    std::cout << "Server started on port " << PORT << std::endl;

    struct ev_loop* loop = ev_default_loop(0);

    ev_io server_watcher;
    ev_io_init(&server_watcher, accept_cb, server_fd, EV_READ);
    ev_io_start(loop, &server_watcher);

    ev_run(loop, 0);

    close(server_fd);
    return 0;
}
