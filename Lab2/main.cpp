#include <iostream>
#include "encrypt_algorithm/des_cbc/descbc.h"
#include "encrypt_algorithm/keys/keys_creator.h"
#include <fstream>

int main() {
    uint64_t key = 0x0123456789abcdef;
    auto keys = des::create_keys(key, 16);
    uint64_t iv = 0x133457799BBCDFF1;
    std::ifstream in("../data/input.bin", std::ios::binary | std::ios::in | std::ios::ate);
    std::ofstream out("../data/encrypt.bin", std::ios::binary | std::ios::out);
    if(!in.is_open()) return -1;
    des::DESCBC algo(keys);
    algo.encrypt_input(in, out, iv);
    in.close();
    out.close();
    std::ifstream in2("../data/encrypt.bin", std::ios::binary | std::ios::in | std::ios::ate);
    std::ofstream out2("../data/output.bin", std::ios::binary | std::ios::out);
    if(!in2.is_open()) return -1;
    algo.decrypt_input(in2, out2, iv);
    in2.close();
    out2.close();
    return 0;
}
