# PIT.DLL - Windows Programmable Interval Timer Library

C++ library for direct hardware access to the 8254 Programmable Interval Timer on Windows systems.

## Overview

Provides low-level access to PIT Channel 0 counter registers through direct port I/O using the inpoutx64 driver. Designed for applications requiring precise timing measurements and hardware interaction.

## Features

- Direct PIT counter register access (ports 0x40-0x41)
- Thread-safe operations with mutex protection
- RAII wrapper for automatic resource management
- Minimal overhead for timing-critical code
- x64 Windows compatibility

## Requirements

- Windows 7 or newer
- x64 architecture
- inpoutx64.dll in application directory

## API Reference

### Core Functions
```cpp
bool PIT::initialize();          // Load driver and initialize
void PIT::shutdown();            // Cleanup resources
uint16_t PIT::read_counter();    // Read current PIT counter value
bool PIT::is_initialized();      // Check initialization status
