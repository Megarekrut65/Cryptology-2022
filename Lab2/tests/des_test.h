#pragma once

#include "doctest.h"
#include "../encrypt_algorithm/des/des.h"
#include "../encrypt_algorithm/keys/keys_creator.h"

TEST_CASE ("DES algorithm test") {
    std::vector<uint64_t> data = {'h', 'e', 'l', 'l', 'o'};
    uint64_t key = 0x0123456789abcdef;
    auto keys = des::create_keys(key, 16);
    des::DES algo(keys);
    std::vector<uint64_t> cipher;
    cipher.reserve(data.size());
    for (uint64_t value: data) {
        cipher.push_back(algo.encrypt(value));
    }
    std::vector<uint64_t> res;
    res.reserve(cipher.size());
    for (uint64_t value: cipher) {
        res.push_back(algo.decrypt(value));
    }
    for (std::size_t i = 0; i < data.size(); i++) {
                CHECK(data[i] == res[i]);
    }
}