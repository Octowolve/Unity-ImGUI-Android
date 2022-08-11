#include "includes/utils.h"

namespace utils{
    bool is_library_loaded(const char *lib) {
        char line[512] = {0};
        FILE *fp = fopen("/proc/self/maps", "rt");
        if (fp != NULL) {
            while (fgets(line, sizeof(line), fp)) {
                if (strstr(line, lib))
                    return true;
            }
            fclose(fp);
        }
        return false;
    }

    lib_info find_library(const char *module_name){
        lib_info library_info{};
        char line[512], mod_name[64];

        FILE *fp = fopen("/proc/self/maps", "rt");
        if (fp != NULL)
        {
            while (fgets(line, sizeof(line), fp))
            {
                if (strstr(line, module_name))
                {
                    sscanf(line, "%llx-%llx %*s %*ld %*s %*d %s",
                           (long long unsigned *)&library_info.start_address,
                           (long long unsigned *)&library_info.end_address, mod_name);

                    library_info.size = (uintptr_t)library_info.end_address - (uintptr_t)library_info.start_address;

                    if (library_info.name.empty())
                        library_info.name = std::string(mod_name);

                    break;
                }
            }
            fclose(fp);
        }
        return library_info;
    }

    uintptr_t get_absolute_address(const char* lib_name, uintptr_t relative_addr){
        return (reinterpret_cast<uintptr_t>(find_library(lib_name).start_address) + relative_addr);
    }

    uintptr_t find_pattern(uint8_t* start, const size_t length, const char* pattern) {
        const char* pat = pattern;
        uint8_t* first_match = 0;
        for (auto current_byte = start; current_byte < (start + length); ++current_byte) {
            if (*pat == '?' || *current_byte == strtoul(pat, NULL, 16)) {
                if (!first_match)
                    first_match = current_byte;
                if (!pat[2])
                    return (uintptr_t)first_match;
                pat += *(uint16_t*)pat == 16191 || *pat != '?' ? 3 : 2;
            }
            else if (first_match) {
                current_byte = first_match;
                pat = pattern;
                first_match = 0;
            }
        } return 0;
    }

    uintptr_t find_pattern_in_module(const char* lib_name, const char* pattern) {
        lib_info lib_info = find_library(lib_name);
        return find_pattern((uint8_t*)lib_info.start_address, lib_info.size, pattern);
    }
}
