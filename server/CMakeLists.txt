cmake_minimum_required(VERSION 3.15)
project(SHF_server)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

add_executable(SHF_server main.cpp)


install(TARGETS SHF_server DESTINATION bin)

