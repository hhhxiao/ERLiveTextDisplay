//clang-format on
#include <fcntl.h>
#include <io.h>
// clang-format of
#include <stdint.h>
#include <stdio.h>

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <thread>

#include "er.h"
#include "hooks.h"
#include "include/logger.h"
#include "logger.h"
#include "mem.h"

void openConsole() {
    if (AllocConsole()) {
        SetConsoleTitle("Debug");
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        INT hCrt = _open_osfhandle((intptr_t)hCon, _O_TEXT);
        FILE* hf = _fdopen(hCrt, "w");
        setvbuf(hf, NULL, _IONBF, 0);
        *stdout = *hf;
        freopen("CONOUT$", "w+t", stdout);  // NOLINT
        DWORD mode;
        // ANSI support
        GetConsoleMode(hCon, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hCon, mode);
    } else {
        throw std::exception("Can not open console");
    }
}

// 各种初始化
DWORD WINAPI start(LPVOID lpParam) {
    openConsole();
    LOG("Dll injected");
    LOG("Process base address is: 0x%lx", mem::va2rva(0));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (!hooks::initilize()) {
        LOG("Can not initilize Hooks");
    } else {
        LOG("Hooks initilize finished");
    }
    LOG("Setup finished");
    volatile bool stop = false;
    while (!stop) {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        //   LOG("Loop!");
        auto ctr = er::playerDeathCount();
        uint32_t death = 0;
        if (ctr > 0) {
            death = ((er::GameDataMan*)(uint64_t)(ctr))->death_count;
            LOG("Player Death count %d %p (%p)", death, &(((er::GameDataMan*)(uint64_t)(ctr))->death_count),
                er::playerDeathCount());
        }
    }

    ExitThread(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
            DisableThreadLibraryCalls(hModule);
        case DLL_PROCESS_DETACH:
        default:
            break;
    }
    return TRUE;
}
