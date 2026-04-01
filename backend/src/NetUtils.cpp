#include "NetUtils.hpp"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

uint32_t NetUtils::ipv4ArrayToUint32(const uint8_t ip[4]) {
    return (static_cast<uint32_t>(ip[0]) << 24) |
           (static_cast<uint32_t>(ip[1]) << 16) |
           (static_cast<uint32_t>(ip[2]) << 8) |
           static_cast<uint32_t>(ip[3]);
}

void NetUtils::uint32ToIpv4Array(uint32_t ipIn, uint8_t ipOut[4]) {
    ipOut[0] = static_cast<uint8_t>((ipIn >> 24) & 0xFF);
    ipOut[1] = static_cast<uint8_t>((ipIn >> 16) & 0xFF);
    ipOut[2] = static_cast<uint8_t>((ipIn >> 8) & 0xFF);
    ipOut[3] = static_cast<uint8_t>(ipIn & 0xFF);
}

InterfaceInfo NetUtils::getInterfaceInfo(const std::string& interface) {
    InterfaceInfo info{};

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        throw std::runtime_error(std::string("Failed to open socket: ") + std::strerror(errno));
    }

    struct ifreq ifr;
    std::memset(&ifr, 0, sizeof(ifr));
    std::snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", interface.c_str());

    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        close(sock);
        throw std::runtime_error(std::string("Failed to get MAC for interface: ") + interface);
    }
    std::memcpy(info.mac, ifr.ifr_hwaddr.sa_data, 6);

    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        close(sock);
        throw std::runtime_error(std::string("Failed to get IP for interface: ") + interface);
    }
    auto* addr = reinterpret_cast<struct sockaddr_in*>(&ifr.ifr_addr);
    std::memcpy(info.ip, &addr->sin_addr.s_addr, 4);

    if (ioctl(sock, SIOCGIFNETMASK, &ifr) < 0) {
        close(sock);
        throw std::runtime_error(std::string("Failed to get netmask for interface: ") + interface);
    }
    auto* mask = reinterpret_cast<struct sockaddr_in*>(&ifr.ifr_netmask);
    std::memcpy(info.netmask, &mask->sin_addr.s_addr, 4);

    close(sock);
    return info;
}
