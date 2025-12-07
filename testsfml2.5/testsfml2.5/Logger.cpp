#include "Logger.h"
#include <iostream>

std::ofstream Logger::ofs;

void Logger::init(const std::string& filename) {
    ofs.open(filename, std::ios::app);
}

void Logger::info(const std::string& msg) {
    std::cout << "[INFO] " << msg << std::endl;
    if (ofs.is_open()) ofs << "[INFO] " << msg << std::endl;
}

void Logger::error(const std::string& msg) {
    std::cerr << "[ERROR] " << msg << std::endl;
    if (ofs.is_open()) ofs << "[ERROR] " << msg << std::endl;
}

void Logger::shutdown() {
    if (ofs.is_open()) ofs.close();
}
