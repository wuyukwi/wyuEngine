set(SRC_FILES
	D3D9Renderer.cpp
	D3D9Renderer.hpp
)

add_library(D3D9Renderer STATIC
${SRC_FILES}
)

target_include_directories(D3D9Renderer PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${ROOT_DIR}/Sources/Platform/Windows
${ROOT_DIR}/External/d3d9/Include
)

target_link_libraries(D3D9Renderer 
Framework
${ROOT_DIR}/External/d3d9/Lib/x64/d3d9.lib
${ROOT_DIR}/External/d3d9/Lib/x64/d3dx9.lib
)