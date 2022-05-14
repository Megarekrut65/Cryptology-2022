#include "keys_creator.h"

namespace des {

    std::vector<uint64_t> create_keys(uint64_t key, int keys_count) {
        std::vector<uint64_t> sub_keys(keys_count);
        key = convert(DESTables::G, key, 64);
        uint32_t left_c = (uint32_t) ((key >> 28) & 0x000000000fffffff),
                right_d = (uint32_t) (key & 0x000000000fffffff);
        for (int i = 0; i < keys_count; i++) {
            int shift = (int) (DESTables::LEFT_SHIFT[i]);
            left_c = ((left_c << shift) & 0x0FFFFFFF) | (left_c >> (28 - shift));
            right_d = ((right_d << shift) & 0x0FFFFFFF) | (right_d >> (28 - shift));
            uint64_t cd = (((uint64_t) left_c) << 28) | (uint64_t) right_d;
            sub_keys[i] = convert(DESTables::H, cd, 56);
        }

        return std::move(sub_keys);
    }
}