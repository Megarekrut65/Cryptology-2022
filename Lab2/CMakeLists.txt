cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab2 main.cpp encrypt_algorithm/des/des_tables.cpp encrypt_algorithm/des/des_tables.h encrypt_algorithm/des/converter.cpp encrypt_algorithm/des/converter.h encrypt_algorithm/des/des.cpp encrypt_algorithm/des/des.h encrypt_algorithm/des_cbc/descbc.cpp encrypt_algorithm/des_cbc/descbc.h encrypt_algorithm/keys/keys_creator.cpp encrypt_algorithm/keys/keys_creator.h tests/des_test.h)
