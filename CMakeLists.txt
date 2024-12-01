cmake_minimum_required(VERSION 3.7)

# 3rdParty======================
set(ROOT_3rdParty ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

project(
    CPUPathTracing
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Release)

add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/rapidobj)

add_subdirectory(source)

# test 
enable_testing()
add_subdirectory(test/glm) 
add_subdirectory(test/tracing) 
