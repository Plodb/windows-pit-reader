#pragma once
#include <cstdint>
#include <stdexcept>

#ifdef _WIN32
    #ifdef PIT_LIB_EXPORTS
        #define PIT_API __declspec(dllexport)
    #else
        #define PIT_API __declspec(dllimport)
    #endif
#else
    #define PIT_API __attribute__((visibility("default")))
#endif

namespace PIT {
    PIT_API bool initialize();
    PIT_API void shutdown();
    PIT_API uint16_t read_counter();
    PIT_API bool is_initialized();
    
    class PIT_API ScopedPIT {
    public:
        ScopedPIT();
        ~ScopedPIT();
        uint16_t read() const;
        bool initialized() const;
        
    private:
        bool init_success;
    };
}