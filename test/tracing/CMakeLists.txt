include(../../common.cmake)

# 包含的目录
include_directories(
  ${ROOT_3rdParty}
  ${CMAKE_SOURCE_DIR}/source/include
)

# 链接的库
link_directories(${ROOT_3rdParty}/lib)

add_executable(test_BVHNode test_BVHNode.cpp)
target_link_libraries(test_BVHNode PRIVATE CPUPathTracing glm)
add_test(NAME test_BVHNode COMMAND test_BVHNode)

# 线程池
add_executable(test_ThreadPool test_ThreadPool.cpp)
target_link_libraries(test_ThreadPool PRIVATE CPUPathTracing glm)
add_test(NAME test_ThreadPool COMMAND test_ThreadPool)

# 球体
add_executable(test_Sphere test_Sphere.cpp)
target_link_libraries(test_Sphere PRIVATE CPUPathTracing glm)
add_test(NAME test_Sphere COMMAND test_Sphere)

# test_simple_dragon
add_executable(test_simple_dragon test_simple_dragon.cpp)
target_link_libraries(test_simple_dragon PRIVATE CPUPathTracing glm)
add_test(NAME test_simple_dragon COMMAND test_simple_dragon)

# test_Plane
add_executable(test_Plane test_Plane.cpp)
target_link_libraries(test_Plane PRIVATE CPUPathTracing glm)
add_test(NAME test_Plane COMMAND test_Plane)

# Scene
add_executable(test_Scene test_Scene.cpp)
target_link_libraries(test_Scene PRIVATE CPUPathTracing glm)
add_test(NAME test_Scene COMMAND test_Scene)

# Lecture13
add_executable(test_Lecture13 test_Lecture13.cpp)
target_link_libraries(test_Lecture13 PRIVATE CPUPathTracing glm)
add_test(NAME test_Lecture13 COMMAND test_Lecture13)
# target_compile_definitions(test_Lecture13 PUBLIC WITH_DEBUG_INFO)

# Lecture14
add_executable(test_Lecture14 test_Lecture14.cpp)
target_link_libraries(test_Lecture14 PRIVATE CPUPathTracing glm)
add_test(NAME test_Lecture14 COMMAND test_Lecture14)
# target_compile_definitions(test_Lecture14 PUBLIC WITH_DEBUG_INFO)
 