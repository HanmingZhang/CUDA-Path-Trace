cmake_minimum_required(VERSION 3.20)

project(CUDA_path_tracer LANGUAGES C CXX CUDA)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Set up include and lib paths
set(EXTERNAL "external")
include_directories("${EXTERNAL}")
include_directories("${EXTERNAL}/include")

set(EXTERNAL_LIB_PATH "${EXTERNAL}/lib/win")

link_directories(${EXTERNAL_LIB_PATH})
list(APPEND CMAKE_LIBRARY_PATH "${EXTERNAL_LIB_PATH}")


# Find up and set up core dependency libs
set(GLFW_INCLUDE_DIR "${EXTERNAL}/include")
set(GLFW_LIBRARY_DIR "${CMAKE_LIBRARY_PATH}")
find_library(GLFW_LIBRARY "glfw3" HINTS "${GLFW_LIBRARY_DIR}")

set(GLEW_INCLUDE_DIR "${EXTERNAL}/include")
set(GLEW_LIBRARY_DIR "${CMAKE_LIBRARY_PATH}")
add_definitions(-DGLEW_STATIC)

find_package(OpenGL)

set(CORELIBS
    "${GLFW_LIBRARY}"
    "${OPENGL_LIBRARY}"
    "${GLEW_LIBRARY}"
    ${GLEW_LIBRARY_DIR}/glew32s
    )

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Enable CUDA debug info in debug mode builds
list(APPEND CUDA_NVCC_FLAGS_DEBUG -G -g)

if (WIN32)
    list(APPEND CORELIBS legacy_stdio_definitions.lib)
endif()

# Crucial magic for CUDA linking
find_package(Threads REQUIRED)
find_package(CUDAToolkit REQUIRED)

set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE ON)
set(CUDA_SEPARABLE_COMPILATION ON)

set(CMAKE_CUDA_ARCHITECTURES 75 80 86 87 89 90 100 110 120)

include_directories(.)
add_subdirectory(stream_compaction)
add_subdirectory(src)

add_executable(${CMAKE_PROJECT_NAME}
    "src/main.h"
    "src/main.cpp"
    )

target_link_libraries(${CMAKE_PROJECT_NAME}
    src
    stream_compaction
    ${CORELIBS}
    )

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
    ${GLEW_INCLUDE_DIR}
)