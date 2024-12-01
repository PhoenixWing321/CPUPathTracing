include(../../common.cmake)

# test_glm
add_executable(test_glm "test_glm.cpp")
target_link_libraries(test_glm glm::glm)
add_test(NAME "test_glm" COMMAND test_glm)

