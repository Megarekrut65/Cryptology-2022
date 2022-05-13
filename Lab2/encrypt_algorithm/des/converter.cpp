#include "converter.h"

namespace des{

    uint64_t convert(const Table &table, uint64_t input, uint8_t input_length) {
        uint64_t res = 0;
        for (TableType item : table) {
            res = (res << 1) | ((input >> (input_length - item)) & 0x01);
        }
        return res;
    }
}
