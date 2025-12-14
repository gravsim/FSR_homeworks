cmake_minimum_required(VERSION 3.16)
project(c_fsr_codes)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)  # GNU99
set(CMAKE_C_FLAGS "-Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign")
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_SOURCE_DIR}/*.c"
)
add_executable(c_fsr_codes ${SRC_FILES}
        informatics/ADT/C.c
        informatics/ADT/F.c
        informatics/ADT/D.c
        informatics/ADT/E.c
        informatics/BST/A.c
        informatics/BST/B.c
        informatics/BST/C.c
        informatics/HQ/A.c
        informatics/HQ/B.c
        informatics/HQ/C.c
        informatics/HQ/D.c
        informatics/HQ/E.c
        informatics/autumn_graphs/A.c
        informatics/autumn_graphs/B.c
        informatics/autumn_graphs/C.c
        informatics/ADT/anj.c
        yandex/01_12_2025_graph/D.c
        yandex/01_12_2025_graph/A.c
        yandex/01_12_2025_graph/B.c
        yandex/01_12_2025_graph/C.c
)
