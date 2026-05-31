#pragma once
#include <string>
#include <vector>
#include "lru.h"
#include "persistence.h"

class Server {
public:
    Server(int port);
    void run();
private:
    int port;
    LRUCache store;
    Persistence persistence{"kv.aof"};
    std::vector<std::string> parse_command(const std::string& command);
    std::string handle_command(const std::vector<std::string>& tokens);
};