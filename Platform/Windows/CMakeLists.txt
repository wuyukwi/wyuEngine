set(MyGameEngineD3D12 "DX12Engie")

set(SRC_FILES
WindowsApplication.cpp
D3D12Application.cpp

WindowsApplication.hpp
            )

add_executable(${MyGameEngineD3D12} 
${SRC_FILES}
)

target_link_libraries(${MyGameEngineD3D12}  ${Framework} ${D3DRHI})

