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
