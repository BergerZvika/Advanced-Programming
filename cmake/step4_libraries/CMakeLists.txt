cmake_minimum_required(VERSION 3.15)
project(VectorLib C)

# Descends into mylib/ and processes its CMakeLists.txt.
# Must come BEFORE any target that links to "vec3".
add_subdirectory(mylib)

add_executable(vecapp main.c)

# Links vec3 into vecapp. Because vec3 declared its include dir PUBLIC,
# vecapp automatically inherits that include path — no extra
# target_include_directories() needed.
target_link_libraries(vecapp PRIVATE vec3)
