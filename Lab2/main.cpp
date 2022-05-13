#include <iostream>
#include "encrypt_algorithm/des/des.h"
#include "encrypt_algorithm/keys/keys_creator.h"

int main() {
    uint64_t key = 0x0123456789abcdef;
    uint64_t data = (int)'y';
    auto keys = des::create_keys(key, 16);
    des::DES algo{keys};
    uint64_t en = algo.encrypt(data);
    std::cout << en << std::endl;
    uint64_t de = algo.decrypt(en);
    std::cout << (char)de << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
