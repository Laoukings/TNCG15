cmake_minimum_required(VERSION 3.5.0)
project(raytracer VERSION 0.1.0 LANGUAGES C CXX)


# Collect all source files in the 'src' and 'include' directories
file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable(Raytracing ${SOURCES} ${HEADERS})

include(CTest)
enable_testing()

