#include "er.h"

#include <winscard.h>

#include <cstdint>

#include "config.h"
#include "logger.h"
#include "mem.h"

namespace er {

    namespace {
        // Signature Cache
        uintptr_t GameDataManSiganture = 0;

        // instance
        struct GameDataMan {
            uint8_t gap[0x94];
            uint32_t death_count;
            static GameDataMan *&instance() {
                static GameDataMan *gameDataMan{nullptr};
                return gameDataMan;
            }
        };

        struct InitState {
            int death_count{0};
            bool inited;
        };
        // variables
        InitState init_states;
    }  // namespace

    void init_signatures() {
        DBG("Init signatures");
        GameDataManSiganture = mem::FingSigWithOffset("48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3", 3, 7);
        DBG("GameDataManSiganture = 0x%p", GameDataManSiganture);
    }
    void try_refresh_instances() {
        if (!GameDataMan::instance() && GameDataManSiganture != 0) {
            GameDataMan::instance() = *reinterpret_cast<GameDataMan **>(GameDataManSiganture);
            DBG("Refresh GameDataMan Instance: 0x%p", GameDataMan::instance());
        }
        if (GameDataMan::instance() && GameDataMan::instance()->death_count > 0 && !init_states.inited) {
            init_states.death_count = GameDataMan::instance()->death_count;
            init_states.inited = true;
        }
    }

    namespace api {

        int death_count() { return GameDataMan::instance() == nullptr ? -1 : GameDataMan::instance()->death_count; }
        int today_death_count() {
            return (init_states.inited ? death_count() - init_states.death_count : 0) + config::death_correction();
        }
    }  // namespace api
}  // namespace er
