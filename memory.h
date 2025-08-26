#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

#include "cache.h"
#include "operations.h"
#include "exclusion_policy.h"

inline const std::unordered_map<std::string, uint8_t> string_to_register_number = {
        {"zero", 0},
        {"ra",   1},
        {"sp",   2},
        {"gp",   3},
        {"tp",   4},
        {"t0",   5},
        {"t1",   6},
        {"t2",   7},
        {"s0",   8},
        {"fp",   8},
        {"s1",   9},
        {"a0",   10},
        {"a1",   11},
        {"a2",   12},
        {"a3",   13},
        {"a4",   14},
        {"a5",   15},
        {"a6",   16},
        {"a7",   17},
        {"s2",   18},
        {"s3",   19},
        {"s4",   20},
        {"s5",   21},
        {"s6",   22},
        {"s7",   23},
        {"s8",   24},
        {"s9",   25},
        {"s10",  26},
        {"s11",  27},
        {"t3",   28},
        {"t4",   29},
        {"t5",   30},
        {"t6",   31},
        {"ZERO", 0},
        {"RA",   1},
        {"SP",   2},
        {"GP",   3},
        {"TP",   4},
        {"T0",   5},
        {"T1",   6},
        {"T2",   7},
        {"S0",   8},
        {"FP",   8},
        {"S1",   9},
        {"A0",   10},
        {"A1",   11},
        {"A2",   12},
        {"A3",   13},
        {"A4",   14},
        {"A5",   15},
        {"A6",   16},
        {"A7",   17},
        {"S2",   18},
        {"S3",   19},
        {"S4",   20},
        {"S5",   21},
        {"S6",   22},
        {"S7",   23},
        {"S8",   24},
        {"S9",   25},
        {"S10",  26},
        {"S11",  27},
        {"T3",   28},
        {"T4",   29},
        {"T5",   30},
        {"T6",   31},
        {"x0",   0},
        {"x1",   1},
        {"x2",   2},
        {"x3",   3},
        {"x4",   4},
        {"x5",   5},
        {"x6",   6},
        {"x7",   7},
        {"x8",   8},
        {"x9",   9},
        {"x10",  10},
        {"x11",  11},
        {"x12",  12},
        {"x13",  13},
        {"x14",  14},
        {"x15",  15},
        {"x16",  16},
        {"x17",  17},
        {"x18",  18},
        {"x19",  19},
        {"x20",  20},
        {"x21",  21},
        {"x22",  22},
        {"x23",  23},
        {"x24",  24},
        {"x25",  25},
        {"x26",  26},
        {"x27",  27},
        {"x28",  28},
        {"x29",  29},
        {"x30",  30},
        {"x31",  31},
        {"X0",   0},
        {"X1",   1},
        {"X2",   2},
        {"X3",   3},
        {"X4",   4},
        {"X5",   5},
        {"X6",   6},
        {"X7",   7},
        {"X8",   8},
        {"X9",   9},
        {"X10",  10},
        {"X11",  11},
        {"X12",  12},
        {"X13",  13},
        {"X14",  14},
        {"X15",  15},
        {"X16",  16},
        {"X17",  17},
        {"X18",  18},
        {"X19",  19},
        {"X20",  20},
        {"X21",  21},
        {"X22",  22},
        {"X23",  23},
        {"X24",  24},
        {"X25",  25},
        {"X26",  26},
        {"X27",  27},
        {"X28",  28},
        {"X29",  29},
        {"X30",  30},
        {"X31",  31},
};

class CPUMemory {
private:
    Cache cache;

    uint32_t program_counter;
    std::vector<int32_t> registers;
public:
    CPUMemory(ExclusionPolicy exclusion_policy = ExclusionPolicy::LRU) :
        program_counter(0),
        registers(32, 0),
        cache(Cache(exclusion_policy)) {}

    uint32_t& GetProgramCounter() {
        return program_counter;
    }
    int32_t& GetRegister(int32_t register_index) {
        return registers[register_index];
    }

    void Load(uint8_t dest, uint64_t source, uint8_t size = 1) {
        registers[dest] = cache.Load(source, size);
    }
    void LoadUnordered(uint8_t dest, uint64_t source, uint8_t size = 1) {
        registers[dest] = cache.LoadUnordered(source, size);
    }
    void Store(uint8_t source, uint64_t address, uint8_t size = 1) {
        cache.Store(registers[source], address, size);
    }


    uint64_t GetHits() const {
        return cache.GetHits();
    }
    uint64_t GetMisses() const {
        return cache.GetMisses();
    }
};
