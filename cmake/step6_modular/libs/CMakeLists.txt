add_subdirectory(geometry)

# Order between geometry and io doesn't matter — neither depends on the other.
add_subdirectory(io)
