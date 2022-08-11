#pragma once

#include <unistd.h>
#include <string>
#include <jni.h>

namespace utils{

    struct lib_info{
        void* start_address;
        void* end_address;
        intptr_t size;
        std::string name;
    };

    bool is_library_loaded(const char *lib);
    lib_info find_library(const char *libraryName);
    uintptr_t get_absolute_address(const char* lib_name, uintptr_t relative_addr);
    uintptr_t find_pattern(uint8_t* start, const size_t length, const char* pattern);
    uintptr_t find_pattern_in_module(const char* lib_name, const char* pattern);
}

