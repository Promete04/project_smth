#pragma once

#include "DeviceNode.hpp"
#include "NetUtils.hpp"
#include "Packets.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <cerrno>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <unistd.h>

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
