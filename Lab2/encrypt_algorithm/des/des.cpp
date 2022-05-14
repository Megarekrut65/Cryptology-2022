#include "des.h"

namespace des {
    const std::size_t DES::iterations = 16;

    uint64_t DES::run(uint64_t input, bool do_encrypt) {
        input = convert(DESTables::IP, input, 64);
        uint32_t left = (uint32_t) (input >> 32) & 0x0FFFFFFFF,
                right = (uint32_t) (input & 0x0FFFFFFFF);
        for (std::size_t i = 0; i < iterations; i++) {
            uint32_t prev_left = left;
            uint64_t sub_key = do_encrypt ? sub_keys[i] : sub_keys[iterations - i - 1];
            left = right;
            right = prev_left ^ f(sub_key, right);
        }
        input = (((uint64_t) right) << 32) | (uint64_t) left;
        return convert(DESTables::IP_1, input, 64);
    }

    uint32_t DES::f(uint64_t key, uint32_t right) {
        uint64_t e = convert(DESTables::E, right, 32);
        e ^= key;
        uint32_t output = 0;
        for (int i = 0; i < 8; ++i) {
            output <<= 4;
            output |= (uint32_t) s_convert(i, (uint8_t) ((e & 0xFC0000000000) >> 42));
            e <<= 6;
        }

        return (uint32_t) convert(DESTables::P, output, 32);;
    }

    char DES::s_convert(int s_index, uint8_t subject) {
        char row = (char) (((subject & 0x20) >> 4) | (subject & 0x01));
        char col = (char) ((subject & 0x1E) >> 1);
        return DESTables::All_S[s_index][16 * row + col];
    }

    DES::DES(const std::vector<uint64_t> &sub_keys) : sub_keys(sub_keys) {}

    uint64_t DES::encrypt(uint64_t input) {
        return run(input, true);
    }

    uint64_t DES::decrypt(uint64_t input) {
        return run(input, false);
    }
}
