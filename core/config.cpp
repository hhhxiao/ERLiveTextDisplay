#include "config.h"

#include <exception>
#include <fstream>
#include <string>

#include "json.hpp"
#include "logger.h"
#include "misc.h"

namespace config {

    namespace {
        std::string fmtString = "";
        int refreshCycle = 5;
        bool debugMode = false;
        std::string dataFilePath = "";
        //
        int deathCorrection = 0;
    }  // namespace
    void init() {
        auto path = misc::thisDllDirectory() / "er_live_text_display.json";
        LOG("Config path is %s", path.string().c_str());
        try {
            std::ifstream f(path);
            nlohmann::json data = nlohmann::json::parse(f);
            fmtString = data["fmt_string"];
            refreshCycle = data.value("refresh_cycle", 5);
            if (refreshCycle <= 0) refreshCycle = 5;
            debugMode = data.value("debug_mode", false);
            dataFilePath = data.value("data_file", "");
            deathCorrection = data["correction"].value("death", 0);

        } catch (std::exception &e) {
            ERR("Can not open config file:%s", path.string().c_str());
        }
    }

    void print_all_info() {
        DBG("Fmt String: %s", fmtString.c_str());
        DBG("Refresh Cycle: %d", refreshCycle);
        DBG("Debug Mode: %d", debugMode);
        DBG("Data File Path: %s", dataFilePath.c_str());
        DBG("Death Correction: %d", deathCorrection);
    }

    int refresh_cycle() { return refreshCycle; }
    std::string fmt_string() { return fmtString; }
    bool debug_mode() { return debugMode; }
    int death_correction() { return deathCorrection; }
    std::string data_file_path() { return dataFilePath; }

}  // namespace config
