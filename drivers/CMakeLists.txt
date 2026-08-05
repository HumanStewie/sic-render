add_library(drivers opengl/gl_rasterizer.cpp )


target_include_directories(drivers PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(drivers PUBLIC core PRIVATE stb_image glfw glm)