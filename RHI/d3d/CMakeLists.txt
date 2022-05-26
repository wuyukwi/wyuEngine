add_library(d3dRHI_lib STATIC
D3D9Renderer.cpp
D3D9Renderer.hpp
)

target_include_directories(d3dRHI_lib PRIVATE 
${PROJECT_SOURCE_DIR}/External/d3d9/Include
)

target_link_libraries(d3dRHI_lib PRIVATE
${PROJECT_SOURCE_DIR}/External/d3d9/Lib/x64/d3d9.lib
${PROJECT_SOURCE_DIR}/External/d3d9/Lib/x64/d3dx9.lib
)
