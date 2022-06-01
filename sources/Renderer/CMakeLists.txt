# Empty
add_subdirectory(Empty)
add_subdirectory(opengl)
IF(${WIN32})
    # Windows specific code
    add_subdirectory(D2d)
    add_subdirectory(d3d)
ENDIF(${WIN32})