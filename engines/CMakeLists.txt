add_library(engines rendering_engine.cpp)

target_include_directories(engines PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(engines PUBLIC drivers)