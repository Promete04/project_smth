#pragma once

#include "DeviceNode.hpp"

#include <cstdint>
#include <string>
#include <vector>

class ArpScanner {
public:
    explicit ArpScanner(const std::string& interface);

    std::vector<Device> scan();

private:
    std::string iface_;

    void sendArpRequest(int sockfd, const uint8_t targetIp[4],
                        const uint8_t srcMac[6], const uint8_t srcIp[4],const uint8_t netmask[4]);

    std::vector<Device> listenForReplies(int sockfd, int timeoutMs);
};
