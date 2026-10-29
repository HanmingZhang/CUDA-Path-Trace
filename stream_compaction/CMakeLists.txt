cmake_minimum_required(VERSION 3.20)
project(stream_compaction LANGUAGES CXX CUDA)

set(SOURCE_FILES
    EfficientStreamCompaction.cu
    EfficientStreamCompaction.h
)

add_library(stream_compaction ${SOURCE_FILES})

target_include_directories(stream_compaction PRIVATE 
    ${GLEW_INCLUDE_DIR}
)

target_link_libraries(stream_compaction PRIVATE 
    ${GLEW_LIBRARY_DIR}/glew32s)
