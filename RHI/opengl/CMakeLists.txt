set(OpenGLRHI "OpenGLRHI")

set(SRC_FILES
OpenGLManager.cpp
OpenGLManager.hpp
${PROJECT_SOURCE_DIR}/External/glad/src/glad.c
)

add_library(${OpenGLRHI} STATIC
${SRC_FILES}
)

target_include_directories(${OpenGLRHI}  PRIVATE 
${PROJECT_SOURCE_DIR}/External/glad/include
${PROJECT_SOURCE_DIR}/External/glfw3/include/
)

target_link_libraries(${OpenGLRHI}  PRIVATE
${PROJECT_SOURCE_DIR}/External/glfw3/prebuilt/win32/glfw3.lib
opengl32.lib
)
