#pragma once

#include <cstdint>
#include <array>

// -------HEADERS-------

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

struct Ipv4Header {
    uint8_t  versionIhl;
    uint8_t  dscpEcn;
    uint16_t totalLength;
    uint16_t identification;
    uint16_t flagsFragmentOffset;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t headerChecksum;
    uint8_t  srcIp[4];
    uint8_t  dstIp[4];
} __attribute__((packed));

struct TcpHeader {
    uint16_t srcPort;
    uint16_t destPort;
    uint32_t seqNum;
    uint32_t ackNum;
    uint8_t  offset_Rsrvd;
    uint8_t  flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgentPtr;

    /*might add options and payload if
        it becomes necessary*/
} __attribute__((packed));

struct UdpHeader {
    uint16_t srcPort;
    uint16_t destPort;
    uint16_t length;
    uint16_t checksum;
} __attribute__((packed));

struct IcmpHeader {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
} __attribute__((packed));

// -------PACKAGES-------

struct ArpPacket {
    EthHeader eth;
    ArpHeader arp;
} __attribute__((packed));

struct TcpPacket {
    EthHeader  eth;
    Ipv4Header ip;
    TcpHeader  tcp;
} __attribute__((packed));

struct UdpPacket {
    EthHeader  eth;
    Ipv4Header ip;
    UdpHeader  udp;
} __attribute__((packed));

struct IcmpPacket {
    EthHeader  eth;
    Ipv4Header ip;
    IcmpHeader icmp;
} __attribute__((packed));

namespace NetUtils {
uint32_t ipv4ArrayToUint32(uint8_t ip[4]);
void uint32ToIpv4Array(uint32_t ipIn, uint8_t ipOut[4]);
}

namespace PacketFactory{
    //ArpPacket createArpPackage();
    //TcpPacket createTcpPacket();
    //UdpPacket createUdpPacket();
    //IcmpPacket createIcmpPacket();

}