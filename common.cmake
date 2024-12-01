cmake_minimum_required(VERSION 3.10)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

include_directories(${ROOT_3rdParty} 
${ROOT_3rdParty}/glm)
