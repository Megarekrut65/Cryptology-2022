#pragma once
#include <sstream>

namespace des{
    using Type = char;
    class DESTables {
    public:
        static const Type IP[64];
        static const Type IP_1[64];
        static const Type E[48];
        static const Type S1[64];
        static const Type S2[64];
        static const Type S3[64];
        static const Type S4[64];
        static const Type S5[64];
        static const Type S6[64];
        static const Type S7[64];
        static const Type S8[64];
        static const Type P[32];
        static const Type G[56];
        static const Type LEFT_SHIFT[16];
        static const Type H[48];
        static std::stringstream table_to_stream(Type table[], std::size_t rows, std::size_t columns);
    };
}

