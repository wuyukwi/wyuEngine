set(D3DRHI "D3DRHI")

set(SRC_FILES
D3D12Manager.cpp
D3D12Manager.hpp
            )

if(LIB)
    add_library(${D3DRHI} STATIC ${SRC_FILES})
else()
    add_library(${D3DRHI} SHARED ${SRC_FILES})
endif(LIB)

target_include_directories(${D3DRHI} PRIVATE 
${PROJECT_SOURCE_DIR}/External/d3d9/Include
)

target_link_libraries(${D3DRHI} PRIVATE
${PROJECT_SOURCE_DIR}/External/d3d9/Lib/x64/d3d9.lib
${PROJECT_SOURCE_DIR}/External/d3d9/Lib/x64/d3dx9.lib
)
