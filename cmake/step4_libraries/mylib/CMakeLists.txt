# Library type options:
#   STATIC    — .a / .lib; merged into executables at link time
#   SHARED    — .so / .dylib / .dll; loaded at runtime
#   MODULE    — like SHARED but for dlopen()-style plugins
#   INTERFACE — no artifact; only carries properties for consumers
add_library(vec3 SHARED
    vector.c
)

# PUBLIC: vec3 itself AND every target linking vec3 get -I<mylib_dir>.
# Consumers can #include "vec3.h" without specifying the full path.
target_include_directories(vec3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# PUBLIC: consumers of vec3 inherit -lm automatically.
target_link_libraries(vec3 PUBLIC m)
