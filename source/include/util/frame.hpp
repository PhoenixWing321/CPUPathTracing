#pragma once

#include <glm/glm.hpp>

class Frame
{
public:

    Frame();
    Frame(const glm::vec3& normal);
    Frame(const glm::vec3& x_axis, const glm::vec3& y_axis);
    Frame(const glm::vec3& x_axis, const glm::vec3& y_axis, const glm::vec3& z_axis);

public:
    glm::vec3 localFromWorld(const glm::vec3& direction_world) const;
    glm::vec3 worldFromLocal(const glm::vec3& direction_local) const;

public:
    glm::vec3 x_axis, y_axis, z_axis;
};
