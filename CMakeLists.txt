cmake_minimum_required(VERSION 3.28)
project([sic]render)

# Setting important variables
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# GLFW extra unneeded building
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# GLFW OS-specific flags
set(GLFW_USE_RETINA ON CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)

# GLM Fix
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

# Assimp settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE) # Strips the exporter subsystem, might need in the future?
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

## Assimp Importer Types
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER ON CACHE BOOL "" FORCE)

# Add vendor subdirectories
add_subdirectory("vendors/assimp-6.0.6")
add_subdirectory("vendors/glfw-3.4")
add_subdirectory("vendors/glad")
add_subdirectory("vendors/stb_image")
add_subdirectory("vendors/glm")

# Add project subdirectories
add_subdirectory("core")
add_subdirectory("drivers")
add_subdirectory("engines")
add_subdirectory("main")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(sic_render PRIVATE
        -O1
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(sic_render PRIVATE
        -fsanitize=address,undefined
    )
    if(CMAKE_C_COMPILER_LOADED)
        set(LSAN_SUPP_FILE "${CMAKE_CURRENT_BINARY_DIR}/lsan_suppressions.c")
    else()
        set(LSAN_SUPP_FILE "${CMAKE_CURRENT_BINARY_DIR}/lsan_suppressions.cpp")
    endif()

    file(WRITE "${LSAN_SUPP_FILE}" [=[
    #ifdef __cplusplus
    extern "C"
    #endif
    __attribute__((used, visibility("default")))
    const char *__lsan_default_options(void) {
        return "detect_leaks=0";
    }
    ]=])

        target_sources(sic_render PRIVATE "${LSAN_SUPP_FILE}")
endif()