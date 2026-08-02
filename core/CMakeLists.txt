add_library(core shader.cpp)

target_compile_definitions(core PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources")

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(core PUBLIC glad)
