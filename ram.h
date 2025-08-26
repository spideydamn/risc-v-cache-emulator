#pragma once

#include <cstdint>
#include <vector>

#include "consts.h"

class RAM {
private:
    std::vector<bool> memory;
public:
    explicit RAM(uint32_t mem_size): memory(mem_size, false) {}

    void Get(std::vector<bool>& dest, uint64_t address) {
        for (uint64_t i = address; i < address + CACHE_LINE_SIZE * BYTE_SIZE; ++i) {
            dest[i - address] = memory[i];
        }
    }
    void Put(const std::vector<bool>& line, uint64_t address) {
        for (uint64_t i = address; i < address + CACHE_LINE_SIZE * BYTE_SIZE; ++i) {
            memory[i] = line[i - address];
        }
    }
};


