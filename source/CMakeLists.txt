project(CPUPathTracing LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp)

add_library(CPUPathTracing ${source})
target_include_directories(CPUPathTracing PUBLIC include ${ROOT_3rdParty} ${ROOT_3rdParty}/glm ${ROOT_3rdParty}/rapidobj/include)
target_compile_definitions(CPUPathTracing PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_RADIANS GLM_FORCE_LEFT_HANDED
    CPUPathTracing PUBLIC WITH_DEBUG_INFO)

# Add the path to the build directory where glm.lib is located
link_directories(${ROOT_3rdParty}/lib)

target_link_libraries(CPUPathTracing glm rapidobj)
