#pragma once
#include <string>
#include <vector>
#include "lru.h"


class Server {
public:
    Server(int port);
    void run();
private:
    int port;
    LRUCache store;
    std::vector<std::string> parse_command(const std::string& command);
    std::string handle_command(const std::vector<std::string>& tokens);
};