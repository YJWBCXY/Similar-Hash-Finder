cmake_minimum_required(VERSION 3.20)
project(SHF_server)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
# include_directories("/usr/local/include/libmongoc-1.0")
# include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

add_executable(SHF_server main.cpp)

target_link_libraries(SHF_server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(SHF_server ${LIBBSONCXX_LIBRARIES})

install(TARGETS SHF_server DESTINATION bin)

