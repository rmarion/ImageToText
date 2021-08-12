cmake_minimum_required(VERSION 3.0)
project(cimagetotext VERSION 1.0.0)

add_subdirectory(src)
add_subdirectory(python)

target_link_libraries(cimagetotext ${ImageMagick_LIBRARIES})
target_link_libraries(cimagetotext ImageToTextConverter)