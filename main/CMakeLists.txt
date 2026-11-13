# Executables
add_executable(sic_render
    "main.cpp"
    "game_engine/game_engine.cpp"
    "window/window.cpp"
    "camera/camera.cpp"
    "input/input.cpp"
    "subsystems/asset_manager.cpp")

target_include_directories(sic_render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sic_render PUBLIC core PRIVATE glad glfw engines glm::glm stb_image)
