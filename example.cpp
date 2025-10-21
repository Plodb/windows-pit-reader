#include "pit_reader.h"
#include <iostream>
#include <thread>

int main() {
    PIT::ScopedPIT pit;
    
    if (pit.initialized()) {
        for (int i = 0; i < 10; ++i) {
            try {
                uint16_t value = pit.read();
                std::cout << "PIT[" << i << "]: " << value << "\n";
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    } else {
        std::cerr << "Failed to initialize PIT\n";
    }
    
    return 0;
}