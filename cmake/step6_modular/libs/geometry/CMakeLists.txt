# STATIC → libgeometry.a; merged into executables at link time.
add_library(geometry STATIC geometry.cpp)

# PUBLIC: geometry itself AND geoapp (which links geometry) both get
# -I<libs/geometry/>, so geoapp can #include "geometry.h" automatically.
target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_compile_features vs CMAKE_CXX_STANDARD:
#   CMAKE_CXX_STANDARD applies to ALL targets in scope.
#   target_compile_features is per-target and propagates via PUBLIC/PRIVATE/INTERFACE.
#   "cxx_std_17" is portable — translated to -std=c++17 or /std:c++17.
target_compile_features(geometry PUBLIC cxx_std_17)
