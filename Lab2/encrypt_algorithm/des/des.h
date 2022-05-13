#pragma once
#include "converter.h"
#include "des_tables.h"
#include <iostream>

namespace des{
    class DES {
    private:
        static const std::size_t iterations;
        const std::vector<uint64_t>&sub_keys;
        uint32_t f(uint64_t key, uint32_t right);
        char s_convert(int s_index, uint8_t subject);
        uint64_t run(uint64_t input, bool do_encrypt);
    public:
        explicit DES(const std::vector<uint64_t> &sub_keys);
        uint64_t encrypt(uint64_t input);
        uint64_t decrypt(uint64_t input);
    };
}


