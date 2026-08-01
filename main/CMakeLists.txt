# Executables
add_executable(sic_render
    "main.cpp"
)

target_link_libraries(sic_render PRIVATE engines glfw glad)
