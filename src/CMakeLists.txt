cmake_minimum_required(VERSION 3.20)
project(src LANGUAGES CXX CUDA)

set(SOURCE_FILES
    "stb.cpp"
    "image.cpp"
    "image.h"
    "interactions.h"
    "intersections.h"
    "glslUtility.hpp"
    "glslUtility.cpp"
    "pathtrace.cu"
    "pathtrace.h"
    "scene.cpp"
    "scene.h"
    "sceneStructs.h"
    "preview.h"
    "preview.cpp"
    "utilities.cpp"
    "utilities.h"
    "tiny_obj_loader.h"
    "tiny_obj_loader.cc"
    "bounds.h"
    "bounds.cpp"
    "bvh.h"
    "bvh.cpp"
    )

add_library(src ${SOURCE_FILES})

target_include_directories(src PRIVATE 
    ${GLEW_INCLUDE_DIR}
)

target_link_libraries(src PRIVATE 
    ${GLEW_LIBRARY_DIR}/glew32s)
