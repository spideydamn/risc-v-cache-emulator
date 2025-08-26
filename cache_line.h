#pragma once

#include <vector>
#include <cstdint>

#include "consts.h"

struct CacheLine {
    CacheLine() : time(0), tag(0), data(CACHE_LINE_SIZE * BYTE_SIZE) {}
    uint64_t time;
    uint64_t tag;
    std::vector<bool> data;
};