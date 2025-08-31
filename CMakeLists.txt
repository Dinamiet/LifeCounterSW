cmake_minimum_required(VERSION 3.20.0)

project(
    LifeCounter
    VERSION
        00.01
)

enable_language(
    C
    ASM
)

add_executable(
    ${PROJECT_NAME}
)

add_subdirectory(stm32cube/cmake/stm32cubemx)

target_link_libraries(
    ${PROJECT_NAME}
    stm32cubemx
)
