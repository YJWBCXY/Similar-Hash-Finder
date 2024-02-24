add_library(Algorithms Algorithms.cpp)
target_include_directories(Algorithms INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           )
target_compile_definitions(Algorithms PUBLIC compiler_flags)