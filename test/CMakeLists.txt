include_directories(${ROOT_DIR}/test)
#set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS" )
add_executable(test main.cpp main.h)
target_link_libraries(test MyGameEngineD3D9_LIB)