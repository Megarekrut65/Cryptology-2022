#pragma once
#include <sstream>
#include <vector>

namespace des{
    using TableType = char;
    using Table = std::vector<TableType>;
    class DESTables {
    public:
        static const Table IP;//[64];
        static const Table IP_1;//[64];
        static const Table E;//[48];
        static const Table S1;//[64];
        static const Table S2;//[64];
        static const Table S3;//[64];
        static const Table S4;//[64];
        static const Table S5;//[64];
        static const Table S6;//[64];
        static const Table S7;//[64];
        static const Table S8;//[64];
        static const Table P;//[32];
        static const Table G;//[56];
        static const Table LEFT_SHIFT;//[16];
        static const Table H;//[48];
        static const Table All_S[8];
        static std::stringstream table_to_stream(const Table& table, std::size_t rows, std::size_t columns);
    };
}

