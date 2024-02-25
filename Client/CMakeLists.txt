find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(shf_client main.cpp window.cpp)

target_include_directories(shf_client INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           )
target_compile_definitions(shf_client PUBLIC compiler_flags)

target_link_libraries(shf_client PUBLIC Algorithms)
target_link_libraries(shf_client PRIVATE Qt6::Widgets)

set_target_properties(shf_client PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(WIN32)
    add_custom_command(
        TARGET shf_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::Widgets>
            $<TARGET_FILE_DIR:shf_client>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::Core>
            $<TARGET_FILE_DIR:shf_client>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::Gui>
            $<TARGET_FILE_DIR:shf_client>
    )
elseif(APPLE)
    set_target_properties(shf_client PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()