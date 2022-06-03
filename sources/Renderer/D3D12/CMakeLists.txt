set(SRC_FILES
	D3D12RendererManager.cpp
	D3D12RendererManager.hpp
)

add_library(D3D12Renderer 
${SRC_FILES}
)

target_include_directories(D3D12Renderer PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${ROOT_DIR}/Sources/Platform/Windows
)

target_link_libraries(D3D12Renderer Framework)