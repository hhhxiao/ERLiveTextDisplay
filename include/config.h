#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace config {

    void init();

    void print_all_info();

    // data
    int refresh_cycle();
    std::string fmt_string();
    bool debug_mode();
    // correction
    int death_correction();
    std::string data_file_path();

}  // namespace config

#endif
