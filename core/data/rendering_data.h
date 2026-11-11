#pragma once
#include <glm/glm.hpp>

namespace RenderData {
    struct DrawData {
        glm::mat4 view{};
        glm::mat4 project{};
        glm::vec3 viewPos{};
        glm::vec3 cameraFront{};
    };
    struct InputData{
        bool seeThrough{};
    };
}