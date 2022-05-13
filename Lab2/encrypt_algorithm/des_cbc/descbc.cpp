#include <bitset>
#include "descbc.h"

namespace des{

    DESCBC::DESCBC(const std::vector<uint64_t> &sub_keys) :sub_keys(sub_keys), des{DES(sub_keys)}{}

    void DESCBC::encrypt_input(std::istream &in, std::ostream &out, uint64_t iv) {
        uint64_t length = in.tellg();
        in.seekg(0, std::ios::beg);
        uint64_t buffer = 0;
        uint64_t prev_c = iv;
        uint64_t current_m;
        std::cout << length << std::endl;
        for (uint64_t i = 0; i < length / 8; i++) {
            in.read((char *) &buffer, 8);
            current_m = buffer;
            prev_c = des.encrypt(current_m ^ prev_c);
            out.write((char *) &prev_c, 8);
        }
    }
    void DESCBC::decrypt_input(std::istream &in, std::ostream &out, uint64_t iv) {
        uint64_t length = in.tellg();
        std::cout << length << std::endl;
        in.seekg(0, std::ios::beg);
        uint64_t buffer = 0;
        uint64_t c_prev = iv;
        uint64_t p_curr;
        for (uint64_t i = 0; i < length / 8; i++) {
            in.read((char *) &buffer, 8);
            p_curr = buffer;
            uint64_t res = des.decrypt(p_curr) ^c_prev;
            out.write((char *) &res, 8);
            c_prev = p_curr;
        }
    }
}