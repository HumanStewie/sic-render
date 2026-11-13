#pragma once

#include "core/types/texture.h"
#include "drivers/opengl/gl_rasterizer.h"
#include <vector>
class AssetManager {
public:
    AssetManager();
    GLuint LoadTextureFromFile(const std::string& path, bool flip);
};