#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_rasterizer.h" 
#include "core/data/rendering_data.h"
#include "core/shader/gl_shader.h"
#include <glm/gtc/random.hpp>
#include <print>
#include "glm/ext/matrix_transform.hpp"
#include "vendors/stb_image/stb_image.h"

// Set up Buffers
GL_Rasterizer::GL_Rasterizer()
    : shader{ RESOURCES_PATH "/shaders/materials/StandardMaterial.vert", RESOURCES_PATH "/shaders/materials/StandardMaterial.frag" }
    , lightShader { RESOURCES_PATH "/shaders/light.vert", RESOURCES_PATH "/shaders/light.frag" }
    , model { RESOURCES_PATH "/assets/backpack/backpack.obj" }
{
    // --- GLOBAL SETTINGS ---
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
}

enum class LightTypes {
    DirLight,
    PointLight,
    SpotLight
};

void GL_Rasterizer::Draw(const RenderData::DrawData& drawData, const RenderData::InputData& inputData) {
    glClearColor(0.2f, 0.2f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    shader.SetMat4f("view", drawData.view);
    shader.SetMat4f("projection", drawData.project);
    shader.SetMat4f("model", modelMatrix);

    shader.SetVec3f("viewPos", drawData.viewPos);

    shader.SetVec3f("dirLight.direction", glm::vec3{1, -1, -1});
    shader.SetVec3f("dirLight.ambient", glm::vec3{0.2f});
    shader.SetVec3f("dirLight.diffuse", glm::vec3{0.8f});
    shader.SetVec3f("dirLight.specular", glm::vec3{1});

    shader.SetUInt("dirLight.type", static_cast<unsigned int>(LightTypes::DirLight));

    model.Draw(shader);
}

GL_Rasterizer::~GL_Rasterizer() {
    
}