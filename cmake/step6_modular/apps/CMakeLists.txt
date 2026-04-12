add_executable(geoapp main.cpp)

# geometry and io declared their headers PUBLIC, so geoapp inherits
# -I<libs/geometry/>, -I<libs/io/>, and -std=c++17 automatically.
# No extra target_include_directories() or target_compile_features() needed.
target_link_libraries(geoapp PRIVATE geometry io)
