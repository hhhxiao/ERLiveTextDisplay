#include "outputer.h"

#include <fmt/format.h>

#include "config.h"
#include "er.h"
#include "fmt/core.h"
#include "logger.h"
#include "misc.h"

TextOutputer::TextOutputer() {
    auto fileName = config::data_file_path();
    if (fileName.empty()) {
        fileName = (misc::thisDllDirectory() / "data.txt").string();
    }
    f.open(fileName, std::ios::out | std::ios::trunc);
    if (!f.is_open()) {
        ERR("Can not open file %s", fileName.c_str());
    }
}
TextOutputer::~TextOutputer() { f.close(); }
void TextOutputer::update() {
    f.seekp(0);                                                        // 移动到文件开头
    f << fmt::format(config::fmt_string(),                             //
                     fmt::arg("death_count", er::api::death_count()),  //
                     fmt::arg("today_death_count", er::api::today_death_count()));
}