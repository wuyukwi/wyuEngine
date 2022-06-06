set(SRC_FILES 
    Common/Allocator.cpp
    Common/MemoryManager.cpp
    Common/BaseApplication.cpp
    Common/RendererManager.cpp 
#    Common/wyuEngine.cpp
    Common/main.cpp
    Common/AssetLoader.cpp
    Common/Texture.cpp
    Common/SceneManager.cpp

    Common/Allocator.hpp
    Common/MemoryManager.hpp
    Common/BaseApplication.hpp
    Common/GfxConfiguration.h
    Common/RendererManager.hpp
#    Common/wyuEngine.hpp
    Common/AssetLoader.hpp
    Common/Buffer.hpp
    Common/utility.hpp
    Common/Image.hpp
    Common/Texture.hpp
    Common/SceneManager.hpp
    Common/SceneObject.hpp
    Common/SceneNode.hpp
    Common/BMP.hpp

    Interface/IApplication.hpp
    Interface/Interface.hpp
    Interface/IRuntimeModule.hpp
    Interface/ImageParser.hpp

    Math/EngineMath.h
    Math/common.h
    Math/Matrix.h
    Math/vector.h
)


add_library(Framework STATIC ${SRC_FILES})

target_include_directories(Framework
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Common
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface
    ${CMAKE_CURRENT_SOURCE_DIR}/Math
)

target_link_libraries(Framework PRIVATE stb crossguid)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})


