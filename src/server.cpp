#include "server.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

Server::Server(int port) : port(port) {}

void Server::run() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "KV Store listening on port " << port << std::endl;

    while (true) {
        SOCKET client_fd = accept(server_fd, nullptr, nullptr);

        char buffer[1024] = {};
        recv(client_fd, buffer, 1024, 0);

        std::string command(buffer);
        std::cout << "Received: " << command << std::endl;

        std::string response = "OK\n";
        send(client_fd, response.c_str(), response.size(), 0);

        closesocket(client_fd);
    }

    WSACleanup();
}