add_executable(OpenGLRHI_lib
opengl.cpp
${PROJECT_SOURCE_DIR}/External/glad/src/glad.c
)

target_include_directories(OpenGLRHI_lib PRIVATE 
${PROJECT_SOURCE_DIR}/External/glad/include
${PROJECT_SOURCE_DIR}/External/glfw3/include/
)

target_link_libraries(OpenGLRHI_lib PRIVATE
${PROJECT_SOURCE_DIR}/External/glfw3/prebuilt/win32/glfw3.lib
opengl32.lib
)
