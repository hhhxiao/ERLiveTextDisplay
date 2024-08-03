#include "er.h"

#include <winscard.h>

#include <cstdint>

#include "include/logger.h"
#include "logger.h"
#include "mem.h"
uint64_t readQword(uintptr_t address) { return *reinterpret_cast<uint64_t *>(address); }

namespace er {

    GameDataMan *&GameDataMan::instance() {
        static GameDataMan *gameDataMan{nullptr};
        return gameDataMan;
    }

    uintptr_t demo_addr;
    uint64_t playerDeathCount() {
        // return GameDataMan::instance() == nullptr ? -1 : GameDataMan::instance()->death_count;
        return demo_addr == 0 ? -1 : readQword(demo_addr);
    }
    void init_hooks() {
        if (!GameDataMan::instance()) {
            // GameDataMan::instance() = reinterpret_cast<GameDataMan *>();

            auto game_data_man_addr =
                mem::FingSigWithOffset("48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3", 3, 7);
            // GameDataMan::instance() = (GameDataMan *)
            demo_addr = game_data_man_addr;
            // DBG("GameDataManAddr = 0x%p realaddress = 0x%p", game_data_man_addr, readQword(game_data_man_addr));
        }
    }
}  // namespace er