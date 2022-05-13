#pragma once
#include "../des/des.h"
#include <iostream>

namespace des{
    class DESCBC {
        const std::vector<uint64_t> &sub_keys;
        DES des;
    public:
        explicit DESCBC(const std::vector<uint64_t> &sub_keys);
        void encrypt_input(std::istream& in, std::ostream& out, uint64_t iv);
        void decrypt_input(std::istream& in, std::ostream& out, uint64_t iv);
    };
}


