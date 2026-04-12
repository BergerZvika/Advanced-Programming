cmake_minimum_required(VERSION 3.15)

# Names the project; enables only the C compiler.
project(MultiFile C)

# Creates "calculator" from two source files, each compiled into its own object
# then linked together. Prefer explicit source lists over file(GLOB) — GLOB
# doesn't re-run CMake when new files are added.
add_executable(calculator
    main.c
    math_utils.c
)
