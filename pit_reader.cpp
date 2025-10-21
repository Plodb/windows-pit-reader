#include "pit_reader.h"
#include <windows.h>
#include <mutex>
#include <atomic>
#include <iostream>

namespace {
    using inpfuncPtr = unsigned short (__stdcall *)(unsigned short);
    using oupfuncPtr = void (__stdcall *)(unsigned short, unsigned short);

    inpfuncPtr inp32 = nullptr;
    oupfuncPtr out32 = nullptr;
    HMODULE hLib = nullptr;
    std::mutex pit_mutex;
    std::atomic<bool> driver_initialized = false;
}

namespace PIT {
    bool initialize() {
        if (driver_initialized) return true;
        
        hLib = LoadLibraryA("inpoutx64.dll");

        if (!hLib) {
            std::cerr << "PIT Error: Failed to load inpoutx64.dll\n";
            return false;
        }

        inp32 = (inpfuncPtr)(void*)GetProcAddress(hLib, "Inp32");
        out32 = (oupfuncPtr)(void*)GetProcAddress(hLib, "Out32");

        if (!inp32 || !out32) {
            std::cerr << "PIT Error: Failed to get Inp32/Out32 functions\n";
            FreeLibrary(hLib);
            hLib = nullptr;
            return false;
        }

        driver_initialized = true;
        return true;
    }

    void shutdown() {
        if (hLib) {
            FreeLibrary(hLib);
            hLib = nullptr;
            inp32 = nullptr;
            out32 = nullptr;
            driver_initialized = false;
        }
    }

    uint16_t read_counter() {
        std::lock_guard<std::mutex> lock(pit_mutex);
        
        if (!driver_initialized) {
            throw std::runtime_error("PIT not initialized");
        }

        out32(0x43, 0x00);
        uint8_t low = inp32(0x40);
        uint8_t high = inp32(0x40);

        return (static_cast<uint16_t>(high) << 8) | low;
    }

    bool is_initialized() {
        return driver_initialized;
    }

    ScopedPIT::ScopedPIT() : init_success(initialize()) {
    }

    ScopedPIT::~ScopedPIT() {
        if (init_success) {
            shutdown();
        }
    }

    uint16_t ScopedPIT::read() const {
        if (!init_success) {
            throw std::runtime_error("PIT not initialized in ScopedPIT");
        }
        return read_counter();
    }

    bool ScopedPIT::initialized() const {
        return init_success;
    }
}