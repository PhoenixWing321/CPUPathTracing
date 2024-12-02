/**
 * @brief right-handed coordinate system without origin point
 *
 * z       y
 * |      /
 * |     /
 * |    /
 * |   /
 * |  /
 * | /
 * |/
 * +------------------> x
 *
 */

#include "util/frame.hpp"

Frame::Frame()
    : x_axis(1, 0, 0)
    , y_axis(0, 1, 0)
    , z_axis(0, 0, 1) {}

Frame::Frame(const glm::vec3& x_axis, const glm::vec3& y_axis, const glm::vec3& z_axis)
    : x_axis(glm::normalize(x_axis))
    , y_axis(glm::normalize(y_axis))
    , z_axis(glm::normalize(z_axis)) {}
Frame::Frame(const glm::vec3& x_axis, const glm::vec3& y_axis)
    : x_axis(glm::normalize(x_axis)) {

    this->z_axis = glm::normalize(glm::cross(x_axis, y_axis));
    this->y_axis = glm::normalize(glm::cross(z_axis, x_axis));
}

Frame::Frame(const glm::vec3& normal) {
    y_axis       = normal;
    glm::vec3 up = glm::abs(normal.y) < 0.99999 ? glm::vec3(0, 1, 0) : glm::vec3(0, 0, 1);
    x_axis       = glm::normalize(glm::cross(up, normal));
    z_axis       = glm::normalize(glm::cross(x_axis, y_axis));
}

glm::vec3 Frame::localFromWorld(const glm::vec3& direction_world) const {
    return glm::normalize(glm::vec3{
        glm::dot(direction_world, x_axis),
        glm::dot(direction_world, y_axis),
        glm::dot(direction_world, z_axis),
    });
}

glm::vec3 Frame::worldFromLocal(const glm::vec3& direction_local) const {
    return glm::normalize(direction_local.x * x_axis + direction_local.y * y_axis +
                          direction_local.z * z_axis);
}
