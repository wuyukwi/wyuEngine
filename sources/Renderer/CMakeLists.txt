# Empty
add_subdirectory(Empty)
add_subdirectory(opengl)
IF(${WIN32})
    # Windows specific code
    add_subdirectory(D2D)
    add_subdirectory(D3D9)
    add_subdirectory(D3D12)
ENDIF(${WIN32})