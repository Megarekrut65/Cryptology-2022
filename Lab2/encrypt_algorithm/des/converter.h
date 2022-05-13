#pragma once
#include <cstddef>
#include "des_tables.h"

namespace des{
    uint64_t convert(const Table& table, uint64_t input, uint8_t input_length);
}


