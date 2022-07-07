# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
project ("pokemon")


add_subdirectory("effect")
add_subdirectory("move")
add_subdirectory("pokemon")
add_subdirectory("effect")
add_subdirectory("playerInput")

add_executable (pokemon "main.cc")


