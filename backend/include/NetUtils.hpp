#pragma once

#include <cstdint>
#include <string>

struct InterfaceInfo {
    uint8_t mac[6];
    uint8_t ip[4];
    uint8_t netmask[4];
};

namespace NetUtils {

uint32_t ipv4ArrayToUint32(const uint8_t ip[4]);

void uint32ToIpv4Array(uint32_t ipIn, uint8_t ipOut[4]);

InterfaceInfo getInterfaceInfo(const std::string& interface);

}