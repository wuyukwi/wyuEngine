cmake_minimum_required(VERSION 3.19)

# プロジェクト名とバージョンを設定
project(wyuEngine VERSION 0.1.0)

# C++14を使用することを指定
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 共有ライブラリを無効化する
set(BUILD_SHARED_LIBS OFF)

# オプションの設定
option(IMGUI "Build imgui" ON)
include(CMakeDependentOption)

# インクルードガードの設定
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# IMGUIがONの場合は、IMGUI_ENABLEの定義を追加
if(IMGUI)
	add_compile_definitions(IMGUI_ENABLE=1)
else()
	add_compile_definitions(IMGUI_ENABLE=0)
endif()

# ルートディレクトリとインストールディレクトリの設定
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")

# engine、Demo、gameディレクトリのCMakeLists.txtを実行
add_subdirectory(engine)
add_subdirectory(Demo)
add_subdirectory(game)
