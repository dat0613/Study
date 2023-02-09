cmake_minimum_required(VERSION 3.22)
project(SimpleGame)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

add_subdirectory(test)