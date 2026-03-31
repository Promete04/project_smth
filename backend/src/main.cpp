#include <iostream>
#include <stdexcept>

#include "ArpScanner.hpp"

int main(int arg, char* argv[]) {
    if (arg < 2) {
        std::cerr << "Usage: " << argv[0] << " <interface>\n";
        std::cerr << "Example: " << argv[0] << " eth0\n";
        return 1;
    }

    try {
        ArpScanner scanner(argv[1]);
        const auto devices = scanner.scan();
        std::cout << "Discovered devices: " << devices.size() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Scan failed: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}