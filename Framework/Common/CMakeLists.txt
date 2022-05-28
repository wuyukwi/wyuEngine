set(Framework "Framework")


set(SRC_FILES 
Allocator.cpp
MemoryManager.cpp
BaseApplication.cpp
GPUManager.cpp 
main.cpp

Allocator.hpp
MemoryManager.hpp
BaseApplication.hpp
GPUManager.hpp
    )


if(LIB)
    add_library(${Framework} STATIC ${SRC_FILES})
else()
    add_library(${Framework} SHARED ${SRC_FILES})
endif()
