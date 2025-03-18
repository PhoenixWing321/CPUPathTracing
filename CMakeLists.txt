cmake_minimum_required(VERSION 3.7)
project(CPUPathTracing_Root LANGUAGES CXX)

# 3rdParty======================
set(ROOT_3rdParty ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(source)

# # test 
enable_testing()
add_subdirectory(test/tracing)
