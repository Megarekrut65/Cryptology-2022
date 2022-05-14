#pragma once

#include "doctest.h"
#include "../encrypt_algorithm/des_cbc/descbc.h"
#include "../encrypt_algorithm/keys/keys_creator.h"
#include <fstream>

namespace private_ {
    void test_encrypt(des::DESCBC algo, uint64_t iv, const std::string &in_file_name, const std::string &out_file_name);

    void test_decrypt(des::DESCBC algo, uint64_t iv, const std::string &in_file_name, const std::string &out_file_name);

    void test_equals(const std::string &in_file_name, const std::string &out_file_name);
}

TEST_CASE ("DES CBC algorithm test") {
    std::string folder = "../tests/data/", format = ".bin";
    std::vector<std::string> inputs = {"input1", "input2", "input3"};
    uint64_t key = 0x0123456789abcdef;
    auto keys = des::create_keys(key, 16);
    uint64_t iv = 0x133457799BBCDFF1;
    des::DESCBC algo(keys);
    for (const std::string &file_name: inputs) {
        std::string in = folder + file_name + format, encrypt = folder + file_name + "_encrypt" + format,
                out = folder + file_name + "_output" + format;
        private_::test_encrypt(algo, iv, in, encrypt);
        private_::test_decrypt(algo, iv, encrypt, out);
        private_::test_equals(in, out);
    }
}

namespace private_ {
    void test_encrypt(des::DESCBC algo, uint64_t iv, const std::string &in_file_name, const std::string &out_file_name) {
        std::ifstream in(in_file_name, std::ios::binary | std::ios::in | std::ios::ate);
                REQUIRE(in.is_open());
        std::ofstream out(out_file_name, std::ios::binary | std::ios::out);
        algo.encrypt_input(in, out, iv);
                CHECK(out.tellp() > 0);
        in.close();
        out.close();
    }

    void test_decrypt(des::DESCBC algo, uint64_t iv, const std::string &in_file_name, const std::string &out_file_name) {
        std::ifstream in(in_file_name, std::ios::binary | std::ios::in | std::ios::ate);
                REQUIRE(in.is_open());
        std::ofstream out(out_file_name, std::ios::binary | std::ios::out);
        algo.decrypt_input(in, out, iv);
                CHECK(out.tellp() > 0);
        in.close();
        out.close();
    }

    void test_equals(const std::string &in_file_name, const std::string &out_file_name) {
        std::ifstream before(in_file_name, std::ios::ate);
                REQUIRE(before.is_open());
        std::ifstream after(out_file_name, std::ios::ate);
                REQUIRE(after.is_open());
                REQUIRE(before.tellg() == after.tellg());
        before.seekg(0, std::ios::beg);
        after.seekg(0, std::ios::beg);
        while (!before.eof() && !after.eof()) {
            std::string line1, line2;
            std::getline(before, line1);
            std::getline(after, line2);
                    CHECK(line1 == line2);
        }
        after.close();
        before.close();
    }
}