cmake_minimum_required(VERSION 3.22)
project(CMakeTutorial)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

add_compile_definitions(NOMINMAX)

add_subdirectory(executable-example)
add_subdirectory(shared-library-example)
add_subdirectory(static-library-example)
add_subdirectory(breakpad-test)

add_dependencies(executable-example static-library-example)
target_link_libraries(executable-example 
PUBLIC 
    static-library-example
)

target_include_directories(executable-example PUBLIC "${CMAKE_SOURCE_DIR}/static-library-example/include")
target_compile_options(breakpad-test PRIVATE -g)