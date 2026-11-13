#include "asset_manager.h"
#include "vendors/stb_image/stb_image.h"

GLuint AssetManager::LoadTextureFromFile(const std::string &path, bool flip) {
    GLuint texture{};

    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrChannels;
    unsigned char* data{ stbi_load((RESOURCES_PATH + path).c_str(), &width, &height, &nrChannels, 0) };
    if (data) {
        int colorFormat{};
        switch (nrChannels) {
        case 2:
            colorFormat = GL_RG;
            break;
        case 3:
            colorFormat = GL_RGB;
            break;
        case 4:
            colorFormat = GL_RGBA;
            break;
        default:
            std::println("What kind of image are you using??? (Number of Color Channels too high)");
            break;
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else std::println("Cannot find image");
    stbi_image_free(data);

    return texture;
}