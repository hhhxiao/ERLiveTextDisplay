//clang-format on
#include <fcntl.h>
#include <io.h>
// clang-format of
#include <stdint.h>
#include <stdio.h>

#include <cstdint>
#include <cstdio>
#include <exception>

#include "hooks.h"
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
    if (!hooks::initilize()) {
        LOG("Can not initilize Hooks");
    } else {
        LOG("Hooks initilize finished");
    }
    LOG("Setup finished");
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
