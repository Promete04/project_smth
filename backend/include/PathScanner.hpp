#pragma once

#include <string>

class PathScanner {
public:
    explicit PathScanner(const std::string& interface);
private:
    std::string iface_;
};
