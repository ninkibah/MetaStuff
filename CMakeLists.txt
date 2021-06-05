cmake_minimum_required(VERSION 3.0)
project(MetaStuff VERSION 0.0.1 LANGUAGES CXX)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}")
    set(METASTUFF_TOP_LEVEL_PROJECT ON)
else()
    set(METASTUFF_TOP_LEVEL_PROJECT OFF)
endif()
message(STATUS "${METASTUFF_TOP_LEVEL_PROJECT}")

add_library(MetaStuff INTERFACE)
target_include_directories(MetaStuff INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include/)
target_compile_options(MetaStuff INTERFACE "-std=c++17")

# build examples
option(WITH_EXAMPLES "Build examples" OFF)

if(WITH_EXAMPLES OR METASTUFF_TOP_LEVEL_PROJECT)
    add_subdirectory(example)
endif()

# install step
include(GNUInstallDirs)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MetaStuff
)
