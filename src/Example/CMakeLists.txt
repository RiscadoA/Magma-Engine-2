file(GLOB_RECURSE EXAMPLE_SRC
    "*.hpp"
    "*.cpp"
)

include_directories(../)
add_executable(Example ${EXAMPLE_SRC})
target_link_libraries(Example Magma)
