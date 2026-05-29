#pragma once
#include <string>
#include <vector>
#include <unordered_map>


class Server {
public:
    Server(int port);
    void run();
private:
    int port;
    std::unordered_map<std::string, std::string> store;
    std::vector<std::string> parse_command(const std::string& command);
    std::string handle_command(const std::vector<std::string>& tokens);
};