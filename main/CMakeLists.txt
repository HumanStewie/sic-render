# Executables
add_executable(sic_render
    "main.cpp"
    "game_engine/game_engine.cpp"
    "window/window.cpp")

target_include_directories(sic_render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sic_render PRIVATE glad glfw engines)
