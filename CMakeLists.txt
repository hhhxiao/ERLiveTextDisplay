cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ERClient)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/third)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_compile_options(/wd4819)
add_library(
        ER_LIB
        #core
        core/hooks.cpp
        tools/logger.cpp
        )

target_link_libraries(ER_LIB ${PROJECT_SOURCE_DIR}/third/minhook/MinHook.x64.lib)

# DLL
add_library(EROutPlay  SHARED dllmain.cpp)
target_link_libraries(EROutPlay ER_LIB)

