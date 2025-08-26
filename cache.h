#pragma once

#include <cmath>
#include <cstdint>
#include <memory>

#include "consts.h"
#include "ram.h"
#include "cache_line.h"
#include "exclusion_policy.h"


inline uint64_t GetLineIndex(uint64_t address) {
    return ((address >> (CACHE_OFFSET_LEN)) & ((1 << CACHE_INDEX_LEN) - 1));
}
inline uint64_t GetOffset(uint64_t address) {
    return (address & ((1 << CACHE_OFFSET_LEN) - 1));
}


inline int64_t LinePartToBits(const std::vector<bool>& line, const std::vector<bool>& next_line, uint64_t offset, uint8_t size) {
    int64_t ans = -((int64_t)line[offset * BYTE_SIZE] << (size * BYTE_SIZE - 1));
    for (uint64_t i = offset * BYTE_SIZE + 1; i < CACHE_LINE_SIZE * BYTE_SIZE; ++i) {
        ans |= line[i];
        ans <<= 1;
    }
    for (uint64_t i = 0; i < ((offset + size) % CACHE_LINE_SIZE) * BYTE_SIZE; ++i) {
        ans |= next_line[i];
        ans <<= 1;
    }
    return ans;
}

inline int64_t LinePartToBits(const std::vector<bool>& line, uint64_t offset, uint8_t size) {
    int64_t ans = -((int64_t)line[offset * BYTE_SIZE] << (size * BYTE_SIZE - 1));
    for (uint64_t i = offset * BYTE_SIZE + 1; i < (offset + size) * BYTE_SIZE; ++i) {
        ans |= line[i];
        ans <<= 1;
    }
    return ans;
}

inline uint64_t LinePartToUnorderedBits(const std::vector<bool>& line, const std::vector<bool>& next_line, uint64_t offset, uint8_t size) {
    uint64_t ans = 0;
    for (uint64_t i = offset * BYTE_SIZE; i < CACHE_LINE_SIZE * BYTE_SIZE; ++i) {
        ans |= line[i];
        ans <<= 1;
    }
    for (uint64_t i = 0; i < ((offset + size) % CACHE_LINE_SIZE) * BYTE_SIZE; ++i) {
        ans |= next_line[i];
        ans <<= 1;
    }
    return ans;
}

inline uint64_t LinePartToUnorderedBits(const std::vector<bool>& line, uint64_t offset, uint8_t size) {
    uint64_t ans = 0;
    for (uint64_t i = offset * BYTE_SIZE; i < (offset + size) * BYTE_SIZE; ++i) {
        ans |= line[i];
        ans <<= 1;
    }
    return ans;
}

inline void PutBitsToLine(int64_t value, std::vector<bool>& line, uint64_t offset, uint8_t size) {
    for (uint64_t i = offset * BYTE_SIZE; i < (offset + size) * BYTE_SIZE; ++i) {
        line[i] = ((value >> (size * BYTE_SIZE - (i - offset * BYTE_SIZE) - 1)) & 1);
    }
}

class Cache {
private:
    RAM ram;

    std::vector<std::vector<CacheLine>> memory;
    std::vector<uint64_t> MRU;

    ExclusionPolicy exclusion_policy;

    int64_t time;

    uint64_t misses;
    uint64_t hits;

    CacheLine& FindLine(uint64_t address) {
        switch (exclusion_policy) {
            case ExclusionPolicy::bit_pLRU:
                return FindLineBitPLRU(address);
            default:
                return FindLineLRU(address);
        }
    }

    CacheLine& FindLineLRU(uint64_t address) {
        ++time;

        uint64_t cache_index = GetLineIndex(address) % CACHE_SETS;

        uint64_t ram_line_number = address >> CACHE_OFFSET_LEN;

        uint64_t cache_block_number = 0;
        bool is_hit = false;
        int64_t oldest_time = INF;

        for (uint64_t i = 0; i < CACHE_WAY; ++i) {
            if (memory[i][cache_index].tag == ram_line_number) {
                cache_block_number = i;
                is_hit = true;
                ++hits;
                break;
            } else if (memory[i][cache_index].time < oldest_time) {
                oldest_time = memory[i][cache_index].time;
                cache_block_number = i;
            }
        }

        CacheLine& cache_line = memory[cache_block_number][cache_index];

        if (!is_hit) {
            ++misses;

            ram.Put(cache_line.data, cache_line.tag << CACHE_OFFSET_LEN);
            ram.Get(cache_line.data, address - GetOffset(address));
        }

        cache_line.time = time;
        cache_line.tag = ram_line_number;

        return cache_line;
    }

    CacheLine& FindLineBitPLRU(uint64_t address) {
        uint64_t cache_index = GetLineIndex(address) % CACHE_SETS;

        uint64_t ram_line_number = address >> CACHE_OFFSET_LEN;

        uint64_t cache_block_number = 0;
        bool is_hit = false;
        bool was_first_zero = false;

        for (uint64_t i = 0; i < CACHE_WAY; ++i) {
            if (memory[i][cache_index].tag == ram_line_number) {
                cache_block_number = i;
                is_hit = true;
                ++hits;
                break;
            } else if (!(MRU[cache_index] & (1 << i)) && !was_first_zero) {
                was_first_zero = true;
                cache_block_number = i;
            }
        }

        CacheLine& cache_line = memory[cache_block_number][cache_index];
        MRU[cache_index] |= (1 << cache_block_number);

        if  (MRU[cache_index] == (1 << CACHE_WAY) - 1) {
            MRU[cache_index] = 0;
        }


        if (!is_hit) {
            ++misses;

            ram.Put(cache_line.data, cache_line.tag << CACHE_OFFSET_LEN);
            ram.Get(cache_line.data, address - GetOffset(address));
        }
        
        MRU[cache_index] |= (1 << cache_block_number);
        cache_line.tag = ram_line_number;

        return cache_line;
    }
public:
    Cache(ExclusionPolicy exclusion_policy = ExclusionPolicy::LRU) : 
        ram(MEM_SIZE),
        memory(CACHE_WAY, std::vector<CacheLine>(CACHE_SETS)),
        MRU(CACHE_SETS, 0),
        exclusion_policy(exclusion_policy),
        time(0), 
        misses(0),
        hits(0) {}

    int64_t Load(uint64_t address, uint8_t size = 1) {
        CacheLine& cache_line = FindLine(address);

        uint64_t offset = GetOffset(address);
        if (offset + size > CACHE_LINE_SIZE) {
            CacheLine& next_cache_line = FindLine(address - offset + CACHE_LINE_SIZE);

            return LinePartToBits(cache_line.data, next_cache_line.data, offset, size);
        }

        return LinePartToBits(cache_line.data, offset, size);
    }

    uint64_t LoadUnordered(uint64_t address, uint8_t size = 1) {
        CacheLine& cache_line = FindLine(address);

        uint64_t offset = GetOffset(address);
        if (offset + size > CACHE_LINE_SIZE) {
            CacheLine& next_cache_line = FindLine(address - offset + CACHE_LINE_SIZE);

            return LinePartToUnorderedBits(cache_line.data, next_cache_line.data, offset, size);
        }

        return LinePartToUnorderedBits(cache_line.data, offset, size);
    }

    void Store(int64_t value, uint64_t address, uint8_t size = 1) {
        CacheLine& cache_line = FindLine(address);

        uint64_t offset = GetOffset(address);
        if (offset + size > CACHE_LINE_SIZE) {
            CacheLine& next_cache_line = FindLine(address - offset + CACHE_LINE_SIZE);

            PutBitsToLine(value >> ((offset + size) % CACHE_LINE_SIZE), cache_line.data, offset, size - (offset + size) % CACHE_LINE_SIZE);
            PutBitsToLine(value, next_cache_line.data, offset, (offset + size) % CACHE_LINE_SIZE);

            return;
        }

        PutBitsToLine(value, cache_line.data, offset, size);
    }


    uint64_t GetHits() const {
        return hits;
    }
    uint64_t GetMisses() const {
        return misses;
    }
};