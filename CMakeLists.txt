cmake_minimum_required(VERSION 3.15)
project(pynverse LANGUAGES C)

add_library(pynverse SHARED
    src/pynverse/_native/matriz.c
    src/pynverse/_native/matrix_api.c
)

target_include_directories(pynverse PRIVATE
    src/pynverse/_native
)

set_target_properties(pynverse PROPERTIES
    OUTPUT_NAME "pynverse"
)

if (WIN32)
    set_target_properties(pynverse PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
else()
    set_target_properties(pynverse PROPERTIES
        PREFIX "lib"
        SUFFIX ".so"
    )
endif()

if (MVSC)
    target_compile_options(pynverse PRIVATE /O2)
else()
    target_compile_options(pynverse PRIVATE -O3)
endif()