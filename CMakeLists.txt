cmake_minimum_required(VERSION 3.15)

project(shf_client)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

add_subdirectory(Algorithms)
add_subdirectory(Client)
add_subdirectory(tests)

