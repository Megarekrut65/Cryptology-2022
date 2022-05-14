#pragma once

#include <vector>
#include <cstdint>
#include "../des/converter.h"
#include "../des/des_tables.h"

namespace des {
    std::vector<uint64_t> create_keys(uint64_t key, int keys_count);
}