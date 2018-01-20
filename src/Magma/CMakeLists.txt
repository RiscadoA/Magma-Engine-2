file(GLOB_RECURSE MAGMA_SRC
    "*.hpp"
    "*.cpp"
)

include_directories(external/glfw/include)
add_library(Magma ${MAGMA_SRC})
link_libraries(glfw ${GLFW_LIBRARIES})

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()