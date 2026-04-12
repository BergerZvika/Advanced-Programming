cmake_minimum_required(VERSION 3.15)
project(ModularProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Processes libs/CMakeLists.txt → defines "geometry" and "io" targets.
# libs/ acts as a grouping layer, keeping the root file short.
add_subdirectory(libs)

# Must come AFTER libs — geoapp links to "geometry" and "io".
add_subdirectory(apps)
