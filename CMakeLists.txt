cmake_minimum_required(VERSION 3.2)

project(knyboard)

set(CMAKE_CXX_STANDARD 17)

#file(GLOB MAP_FILES maps/*.map)

file(GLOB GENERATOR_FILES
    src/knyfile.h
    src/knyfile.cpp
    src/generator.cpp
)
add_executable(generator ${GENERATOR_FILES})

set(MAP_FILE "${CMAKE_CURRENT_LIST_DIR}/maps/32x32.map")
set(PCH_H_FILE "${CMAKE_CURRENT_BINARY_DIR}/knyplainarray.h")
set(PCH_CPP_FILE "${CMAKE_CURRENT_BINARY_DIR}/knyplainarray.cpp")
add_custom_command(
    OUTPUT
        "${PCH_H_FILE}"
        "${PCH_CPP_FILE}"
    COMMAND "generator" "KnyPlainArray" "${MAP_FILE}"
        "${PCH_H_FILE}"
        "${PCH_CPP_FILE}"
    DEPENDS "generator"
    COMMENT "Updating PCH"
)

file(GLOB MAIN_FILES
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${MAIN_FILES}
    "${PCH_H_FILE}"
    "${PCH_CPP_FILE}"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/src"
)
