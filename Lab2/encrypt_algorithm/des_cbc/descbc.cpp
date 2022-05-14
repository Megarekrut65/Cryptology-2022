#include "descbc.h"

namespace des {
    const uint64_t DESCBC::expander = 0xFFFFFFFFFFFFFFFF;

    DESCBC::DESCBC(const std::vector<uint64_t> &sub_keys) : des{DES(sub_keys)} {}

    void DESCBC::encrypt_input(std::istream &in, std::ostream &out, uint64_t iv) {
        std::streamsize length = in.tellg();
        in.seekg(0, std::ios::beg);
        uint64_t buffer = 0;
        uint64_t prev_c = iv;
        std::streamsize size = length % 8 == 0 ? length / 8 - 1 : length / 8;
        for (std::streamsize i = 0; i < size; i++) {
            in.read((char *) &buffer, 8);
            prev_c = des.encrypt(buffer ^ prev_c);
            out.write((char *) &prev_c, 8);
        }
        std::streamsize part = length % 8;
        buffer = 0;
        in.read((char *) &buffer, part != 0 ? part : 8);
        buffer ^= expander;
        prev_c = des.encrypt(buffer ^ prev_c);
        out.write((char *) &prev_c, 8);
    }

    void DESCBC::decrypt_input(std::istream &in, std::ostream &out, uint64_t iv) {
        std::streamsize length = in.tellg();
        in.seekg(0, std::ios::beg);
        uint64_t buffer = 0;
        uint64_t c_prev = iv;
        uint64_t res;
        for (std::streamsize i = 0; i < length / 8 - 1; i++) {
            in.read((char *) &buffer, 8);
            res = des.decrypt(buffer) ^ c_prev;
            out.write((char *) &res, 8);
            c_prev = buffer;
        }
        in.read((char *) &buffer, 8);
        res = des.decrypt(buffer) ^ c_prev;
        res ^= expander;
        out.write((char *) &res, (std::streamsize) get_number_real_byte_size(res));
    }

    std::size_t DESCBC::get_number_real_byte_size(uint64_t value) {
        std::stringstream stream;
        stream << std::bitset<64>(value);
        std::string str = stream.str();
        std::size_t index = 0;
        while (str[index] != '1' && !str.empty()) {
            str = str.substr(1, str.length());
        }
        std::size_t size = str.size();
        return size % 8 == 0 ? size / 8 : size / 8 + 1;
    }
}