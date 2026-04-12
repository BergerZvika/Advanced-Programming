# FetchContent was already included in the parent; repeating include() is harmless.
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
    GIT_SHALLOW    TRUE
)

# After this:
#   Catch2::Catch2         — headers + you supply main()
#   Catch2::Catch2WithMain — headers + Catch2 supplies main() (most common)
FetchContent_MakeAvailable(Catch2)

# Helper to avoid repeating boilerplate for every test binary.
function(add_catch_test test_name source_file)

    add_executable(${test_name} ${source_file})

    # Catch2::Catch2WithMain provides main(); mathlib is the code under test.
    # mathlib's PUBLIC include dir (-Isrc/) propagates here automatically.
    target_link_libraries(${test_name} PRIVATE Catch2::Catch2WithMain mathlib)

    # CMAKE_SOURCE_DIR always points to the top-level root
    # regardless of which subdirectory this file is in.
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/src)

    # Loads the catch_discover_tests() helper bundled with Catch2.
    include(Catch)

    # Registers each TEST_CASE as its own CTest entry so you can
    # re-run only failed cases (ctest -R "name") and parallelize (ctest -j8).
    catch_discover_tests(${test_name})

endfunction()

add_catch_test(test_basic       test_basic.cpp)
add_catch_test(test_edge_cases  test_edge_cases.cpp)
