#include <iostream>
#include "DES/tables/des_tables.h"


int main() {
    std::cout << des::DESTables::table_to_stream(const_cast<des::Type *>(des::DESTables::P), 8, 4).str() << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
