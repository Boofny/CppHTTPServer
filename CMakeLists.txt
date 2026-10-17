cmake_minimum_required(VERSION 3.16)
project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # this fixed lsp problem

file(GLOB SOURCES src/*.cpp)

add_executable(server ${SOURCES})

if (MSVC)
    target_compile_options(server PRIVATE /W4)
else()
    target_compile_options(server PRIVATE -Wall -Wextra)
endif()

target_link_libraries(server PRIVATE jsoncpp)

target_include_directories(server
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
