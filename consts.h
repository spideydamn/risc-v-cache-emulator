#pragma once

#include <cstdint>
#include <cmath>

const uint8_t BYTE_SIZE = 8;

const uint32_t MEM_SIZE = 512 * 1024;
const uint16_t CACHE_SIZE = 2048;

const uint8_t CACHE_LINE_SIZE = 32;
const uint8_t CACHE_LINE_COUNT = CACHE_SIZE / CACHE_LINE_SIZE;
const uint8_t CACHE_OFFSET_LEN = (uint8_t)std::log2(CACHE_LINE_SIZE);


const uint8_t CACHE_SETS = 16;
const uint8_t CACHE_INDEX_LEN = (uint8_t)std::log2(CACHE_SETS);

const uint8_t CACHE_WAY = CACHE_LINE_COUNT / CACHE_SETS;

const uint8_t CACHE_TAG_LEN = (uint8_t)std::log2(MEM_SIZE * CACHE_WAY / CACHE_SIZE);

const uint8_t ADDR_LEN = CACHE_TAG_LEN + CACHE_INDEX_LEN + CACHE_OFFSET_LEN;


const int64_t INF = 1e18;
