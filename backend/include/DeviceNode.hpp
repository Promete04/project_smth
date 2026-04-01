#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Service {
    int         port;
    std::string name;
    std::string protocol; 
};

struct Device {
    uint8_t  ip[4];
    uint8_t  mac[6];
    std::string hostname;
    std::vector<std::string> roles;
    std::string status;
    std::vector<Service> services;
};
