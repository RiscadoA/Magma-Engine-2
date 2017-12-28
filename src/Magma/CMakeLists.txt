file(GLOB_RECURSE MAGMA_SRC
    "*.hpp"
    "*.cpp"
)

add_library(Magma ${MAGMA_SRC})