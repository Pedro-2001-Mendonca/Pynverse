cmake_minimum_required(VERSION 3.15)
project(pynverse LANGUAGES C)

find_package(Python REQUIRED COMPONENTS Development NumPy)

Python_add_library(core MODULE
    src/pynverse/_native/core.c
    src/pynverse/_native/matriz.c
    src/pynverse/_native/matrix_api.c
)

target_include_directories(core PRIVATE
    src/pynverse/_native
    ${Python_INCLUDE_DIRS}
    ${Python_NumPy_INCLUDE_DIRS}
)

target_link_libraries(core PRIVATE Python::Python)

install(TARGETS core
    LIBRARY DESTINATION pynverse/_native
    RUNTIME DESTINATION pynverse/_native
)
