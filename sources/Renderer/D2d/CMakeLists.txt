add_library(D2DRenderer
D2DRenderer.cpp
D2DRenderer.hpp
)

target_include_directories(D2DRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(D2DRenderer Framework WindowsApplication)