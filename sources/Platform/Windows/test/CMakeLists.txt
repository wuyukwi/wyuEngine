add_executable(TextureLoadTest TextureLoadTest.cpp)
target_link_libraries(TextureLoadTest WindowsApplication Framework D2DRenderer d2d1 stb)

add_test(NAME TEST_TextureLoad COMMAND TextureLoadTest)

#set_property(TARGET TextureLoadTest PROPERTY WIN32_EXECUTABLE ON)
