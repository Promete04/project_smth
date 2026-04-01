#include "Packets.hpp"

uint32_t NetUtils::ipv4ArrayToUint32(uint8_t ip[4]) {
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

