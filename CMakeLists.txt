cmake_minimum_required(VERSION 3.24)
project([sic]render)

# Setting important variables
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW extra unneeded building
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# GLFW OS-specific flags
set(GLFW_USE_RETINA ON CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)

# Add vendor subdirectories
add_subdirectory("vendors/glfw-3.4")
add_subdirectory("vendors/glad")

# Add project subdirectories
add_subdirectory("drivers")
add_subdirectory("engines")
add_subdirectory("main")


# Compile definitions
target_compile_definitions(sic_render PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources")