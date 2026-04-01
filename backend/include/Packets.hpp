#pragma once

#include <cstdint>

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




