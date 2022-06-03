set(SRC_FILES
	D3D9RendererManager.cpp
	D3D9RendererManager.hpp
)

add_library(D3D9Renderer STATIC
${SRC_FILES}
)

target_include_directories(D3D9Renderer PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${ROOT_DIR}/Sources/Platform/Windows
)

target_link_libraries(D3D9Renderer Framework)