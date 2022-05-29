set(SRC_FILES
	OpenGLManager.cpp
	OpenGLManager.hpp
	${ROOT_DIR}/External/glad/src/glad.c
)

add_library(OpenGLRenderer STATIC
${SRC_FILES}
)

target_include_directories(OpenGLRenderer  INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR}
PRIVATE
${ROOT_DIR}/External/glad/include
${ROOT_DIR}/External/glfw3/include/
)

target_link_libraries(OpenGLRenderer  PRIVATE
${ROOT_DIR}/External/glfw3/prebuilt/win32/glfw3.lib
opengl32.lib
Framework
)
