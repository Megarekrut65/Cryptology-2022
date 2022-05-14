#pragma once
#include "../des/des.h"
#include <iostream>
#include <bitset>

namespace des{
    class DESCBC {
        static const uint64_t expander;
        const std::vector<uint64_t> &sub_keys;
        DES des;
        std::size_t get_number_real_byte_size(uint64_t value);
    public:
        explicit DESCBC(const std::vector<uint64_t> &sub_keys);
        void encrypt_input(std::istream& in, std::ostream& out, uint64_t iv);
        void decrypt_input(std::istream& in, std::ostream& out, uint64_t iv);
    };
}


