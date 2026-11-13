# [sic]render - PS1/PS2-style Game Engine
(name is subject to change, im bad a naming)

I have always loved the PS1/PS2 aesthetic in video games. The jagged edges, the low poly model and low resolution textures, all of it. Which was why I set out to make this game engine. While I'm actively working on my own PS1/PS2-style games on other game engines, I will be working on this. The special features of this engine is built-in ray-tracing, vertex morphing, affine texture mappings, etc. to emulate the retro aesthetic. (Idk what I'm talking about right now, so this too will be subject to change)

## Specifications
- OpenGL 4.6
- GLAD2
- GLFW 3.4
- C++23
- GLM 1.0.3
- stb_image
- Assimp 6.0.6

## TODO
- **Optimize basic lightings:** As is every engine, I need to optimize the shaders for basic Phong Lighting.
- **Better input handling:** Right now we are forced to do really whacky maneuver to go from checking for input to passing data to rasterizer. I will be studying Godot and Hell Engine for this.
- **Model Importer:** No way to import models rn, need that
