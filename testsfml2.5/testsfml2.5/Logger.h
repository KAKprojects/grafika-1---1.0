#pragma once
#include <string>
#include <fstream>

class Logger {
public:
    static void init(const std::string& filename);
    static void info(const std::string& msg);
    static void error(const std::string& msg);
    static void shutdown();
private:
    static std::ofstream ofs;
};
