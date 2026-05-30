#include "server.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

Server::Server(int port) : port(port), store(5) {}

//splits "set name Alice" into ["set", "name", "Alice"]

std::vector<std::string> Server::parse_command(const std::string& command) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = command.find(' ', start)) != std::string::npos) {
        tokens.push_back(command.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(command.substr(start));
    return tokens;
}

//takes token and does the actual work of setting/getting/deleting keys
std::string Server::handle_command(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return "ERROR: Empty command\n";

    const std::string& cmd = tokens[0];
    if (cmd == "set") {
        if (tokens.size() != 3) return "ERROR: Usage: set <key> <value>\n";
        store.put(tokens[1], tokens[2]);
        return "OK\n";
    } else if (cmd == "get") {
        if (tokens.size() != 2) return "ERROR: Usage: get <key>\n";
        return store.get(tokens[1]) + "\n";
    } else if (cmd == "delete") {
        if (tokens.size() != 2) return "ERROR: Usage: delete <key>\n";
        store.remove(tokens[1]);
        return "OK\n";
    }
    return "ERROR: Unknown command\n";
}

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
         
        //trim \r \n and trailing spaces 
        while (!command.empty() && (command.back() == '\r' || command.back() == '\n' || command.back() == ' ')) {
            command.pop_back();
        }
        std::cout << "Received: " << command << std::endl;

        std::vector<std::string> tokens = parse_command(command);
        std::string response = handle_command(tokens);
        send(client_fd, response.c_str(), response.size(), 0);

        closesocket(client_fd);
    }

    WSACleanup();
}