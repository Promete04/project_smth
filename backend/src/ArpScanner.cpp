
#include "ArpScanner.hpp"

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

// Packet Structure

struct EthHeader {
    uint8_t  dest[6];
    uint8_t  src[6];
    uint16_t type;
} __attribute__((packed));

struct ArpHeader {
    uint16_t hwType;
    uint16_t protoType;
    uint8_t  hwSize;
    uint8_t  protoSize;
    uint16_t opcode;
    uint8_t  senderMac[6];
    uint8_t  senderIp[4];
    uint8_t  targetMac[6];
    uint8_t  targetIp[4];
} __attribute__((packed));

struct ArpPacket {
    EthHeader eth;
    ArpHeader arp;
} __attribute__((packed));

//  Display helpers

static void printIp(const uint8_t ip[4]) {
    printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

static void printMac(const uint8_t mac[6]) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

//---------------------

ArpScanner::ArpScanner(const std::string& interface)
    : iface_(interface) {}


bool ArpScanner::getInterfaceInfo(uint8_t mac[6], uint8_t ip[4],uint8_t netmask[4]) {

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return false;

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, iface_.c_str(), IFNAMSIZ - 1);

    // Get MAC 
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        close(sock);
        return false;
    }
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

    // Get IP 
    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        close(sock);
        return false;
    }
    struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(&ifr.ifr_addr);
    memcpy(ip, &addr->sin_addr.s_addr, 4);

    if(ioctl(sock, SIOCGIFNETMASK, &ifr) < 0) {
        close(sock);
        return false;
    }

    struct sockaddr_in* mask = reinterpret_cast<struct sockaddr_in*>(&ifr.ifr_netmask);
    memcpy(netmask, &mask->sin_addr.s_addr, 4);

    close(sock);
    return true;
}



void ArpScanner::sendArpRequest(int sockfd,
                                 const uint8_t targetIp[4],
                                 const uint8_t srcMac[6],
                                 const uint8_t srcIp[4],
                                 const uint8_t netmask[4]) {
    ArpPacket packet;
    memset(&packet, 0, sizeof(packet));

    // Ethernet header
    memset(packet.eth.dest, 0xFF, 6);           // broadcast
    memcpy(packet.eth.src,  srcMac, 6);
    packet.eth.type = htons(ETH_P_ARP);

    // ARP header
    packet.arp.hwType    = htons(1);
    packet.arp.protoType = htons(0x0800);
    packet.arp.hwSize    = 6;
    packet.arp.protoSize = 4;
    packet.arp.opcode    = htons(1);            // REQUEST

    memcpy(packet.arp.senderMac, srcMac,   6);
    memcpy(packet.arp.senderIp,  srcIp,    4);
    memset(packet.arp.targetMac, 0x00,     6); 
    memcpy(packet.arp.targetIp,  targetIp, 4);

    struct sockaddr_ll addr;
    memset(&addr, 0, sizeof(addr));
    addr.sll_ifindex = if_nametoindex(iface_.c_str());
    addr.sll_halen   = ETH_ALEN;
    memset(addr.sll_addr, 0xFF, 6);

    sendto(sockfd, &packet, sizeof(packet), 0,
           reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
}


std::vector<Device> ArpScanner::listenForReplies(int sockfd, int timeoutMs) {
    
    std::vector<Device> found;

    struct timeval tv;
    tv.tv_sec  = timeoutMs / 1000;
    tv.tv_usec = (timeoutMs % 1000) * 1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    uint8_t buffer[sizeof(ArpPacket)];

    while (true) {
        ssize_t len = recv(sockfd, buffer, sizeof(buffer), 0);
        if (len < 0) break;
        if (len < (ssize_t)sizeof(ArpPacket)) continue;

        auto* eth = reinterpret_cast<EthHeader*>(buffer);
        auto* arp = reinterpret_cast<ArpHeader*>(buffer + sizeof(EthHeader));

        if (ntohs(eth->type)   != ETH_P_ARP) continue;
        if (ntohs(arp->opcode) != 2)         continue;  // only REPLY

        // Check for duplicates 
        bool exists = false;
        for (const auto& d : found) {
            if (memcmp(d.mac, arp->senderMac, 6) == 0) {
                exists = true;
                break;
            }
        }
        if (exists) continue;

        Device node;
        memcpy(node.ip,  arp->senderIp,  4);
        memcpy(node.mac, arp->senderMac, 6);
        node.status = "Up";

        printf("  Found: ");
        printIp(node.ip);
        printf("  (");
        printMac(node.mac);
        printf(")\n");

        found.push_back(node);
    }

    return found;
}


std::vector<Device> ArpScanner::scan() {

    uint8_t srcMac[6];
    uint8_t srcIp[4];
    uint8_t netmask[4];


    uint8_t networkBase[4];
    uint8_t broadcast[4];


    if (!getInterfaceInfo(srcMac, srcIp, netmask)) {
        throw std::runtime_error("Could not get interface info: " + iface_);
    }

    printf("Interface: %s  MAC: ", iface_.c_str());
    printMac(srcMac);
    printf("  IP: ");
    printIp(srcIp);
    printf("  Netmask  ");
    printIp(netmask);
    printf("\n");

    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0) {
        throw std::runtime_error(std::string("Failed to open raw socket: ") + std::strerror(errno));
    }

    for (int i = 0; i < 4; ++i) {
        networkBase[i] = static_cast<uint8_t>(srcIp[i] & netmask[i]);
        broadcast[i] = static_cast<uint8_t>(networkBase[i] | static_cast<uint8_t>(~netmask[i]));
    }

    printf("Network base: ");
    printIp(networkBase);
    printf("  Broadcast: ");
    printIp(broadcast);
    printf("\n");

    uint32_t networkInt =
        (static_cast<uint32_t>(networkBase[0]) << 24) |
        (static_cast<uint32_t>(networkBase[1]) << 16) |
        (static_cast<uint32_t>(networkBase[2]) << 8) |
        static_cast<uint32_t>(networkBase[3]);

    uint32_t broadcastInt =
        (static_cast<uint32_t>(broadcast[0]) << 24) |
        (static_cast<uint32_t>(broadcast[1]) << 16) |
        (static_cast<uint32_t>(broadcast[2]) << 8) |
        static_cast<uint32_t>(broadcast[3]);

    if (broadcastInt <= networkInt + 1) {
        close(sockfd);
        throw std::runtime_error("Subnet has no usable host addresses for ARP scan.");
    }

    int sent = 0;
    for (uint32_t host = networkInt + 1; host < broadcastInt; ++host) {
        uint8_t targetIp[4] = {
            static_cast<uint8_t>((host >> 24) & 0xFF),
            static_cast<uint8_t>((host >> 16) & 0xFF),
            static_cast<uint8_t>((host >> 8) & 0xFF),
            static_cast<uint8_t>(host & 0xFF)
        };

        // Skip our own interface address.
        if (memcmp(targetIp, srcIp, 4) == 0) {
            continue;
        }

        sendArpRequest(sockfd, targetIp, srcMac, srcIp, netmask);
        ++sent;
    }

    printf("Requests sent: %d\n", sent);

    printf("Requests sent, listening for replies...\n");

    std::vector<Device> devices = listenForReplies(sockfd, 2000);

    printf("Scan complete. Found %zu devices.\n", devices.size());

    close(sockfd);
    return devices;
}