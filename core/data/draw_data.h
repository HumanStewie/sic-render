#pragma once

#include <glm/glm.hpp>

struct DrawData {
    glm::mat4 view{};
    glm::mat4 project{};
    glm::vec3 viewPos{};
};