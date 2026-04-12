add_library(io STATIC io.cpp)

# Exposes libs/io/ so consumers can #include "io.h" without a prefix.
target_include_directories(io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Requires and propagates C++17. When geoapp links both geometry and io,
# CMake takes the union of required features — no conflict.
target_compile_features(io PUBLIC cxx_std_17)
