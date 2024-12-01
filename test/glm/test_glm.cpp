#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <glm/glm.hpp>
#include <iostream>

using std::cout;
using std::endl;

TEST_CASE("test_glm_vec3", "[glm]") {
    // 声明
    glm::vec3 vec = {1, 2, 6};
    cout << "Hello World !" << endl;
    cout << vec.x << "," << vec.y << "," << vec.z << endl;

    // 测试
    CHECK(vec.x == 1);
    CHECK(vec.y == 2);
    CHECK(vec.z == 6);
}
