#ifndef ER_H
#define ER_H

#include <cstdint>
namespace er {
    void init_hooks();

    struct GameDataMan {
        uint8_t gap[0x94];
        uint32_t death_count;
        static GameDataMan*& instance();
    };

    // apis

    uint64_t playerDeathCount();
}  // namespace er

#endif
