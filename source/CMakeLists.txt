project(CPUPathTracing LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp)

add_library(CPUPathTracing STATIC ${source})
target_include_directories(CPUPathTracing PUBLIC include ${ROOT_3rdParty} ${ROOT_3rdParty}/glm ${ROOT_3rdParty}/rapidobj/include)
target_compile_definitions(CPUPathTracing PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS GLM_FORCE_LEFT_HANDED
    CPUPathTracing PUBLIC WITH_DEBUG_INFO)

# Set output directories based on configuration
set_target_properties(CPUPathTracing PROPERTIES 
    COMPILE_PDB_NAME CPUPathTracing
    COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)
 
# message(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE:CPUPathTracing>)
# 复制命令
# add_custom_command(TARGET CPUPathTracing POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/../Phoenix3rdParty/lib
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CPUPathTracing> ${CMAKE_SOURCE_DIR}/../Phoenix3rdParty/lib/
#     COMMAND ${CMAKE_COMMAND} -E $<IF:$<CONFIG:Debug>,copy,echo> ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/CPUPathTracing.pdb ${CMAKE_SOURCE_DIR}/../Phoenix3rdParty/lib/
# )
