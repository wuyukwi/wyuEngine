set(ENGINE_ROOT_DIR "${ROOT_DIR}/engine") # エンジンルートディレクトリのパスを指定
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/3rdparty") # 3rd partyライブラリのパスを指定
set(ENGINE_ASSET_DIR "/asset") # エンジンのアセットディレクトリのパスを指定

add_subdirectory(3rdparty) # 3rd partyライブラリをビルド

set(TARGET_NAME Engine) # ターゲット名を指定

set(CMAKE_CXX_STANDARD 14) # C++標準を14に指定
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++標準が必要となることを設定

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h) # ヘッダーファイルを検索
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp) # ソースファイルを検索

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ENGINE_HEADERS} ${ENGINE_SOURCES}) # ソースファイルとヘッダーファイルをグループ化

add_library(${TARGET_NAME} ${ENGINE_HEADERS} ${ENGINE_SOURCES}) # ターゲットを追加

set(d3d9_lib ${THIRD_PARTY_DIR}/d3d9/lib/x64/d3d9.lib) # DirectX9のd3d9.libへのパスを指定
set(d3dx9_lib ${THIRD_PARTY_DIR}/d3d9/lib/x64/d3dx9.lib) # DirectX9のd3dx9.libへのパスを指定
set(dinput8_lib ${THIRD_PARTY_DIR}/d3d9/lib/x64/dinput8.lib) # DirectX9のdinput8.libへのパスを指定
set(xinput.lib ${THIRD_PARTY_DIR}/d3d9/lib/x64/xinput.lib) # DirectX9のxinput.libへのパスを指定
set(dxguid_lib ${THIRD_PARTY_DIR}/d3d9/lib/x64/dxguid.lib) # DirectX9のdxguid.libへのパスを指定
set(xaudio2_lib xaudio2.lib) # XAudio2ライブラリへのパスを指定

target_link_libraries(${TARGET_NAME} PUBLIC ${d3d9_lib}) # d3d9.libをリンク
target_link_libraries(${TARGET_NAME} PUBLIC ${d3dx9_lib}) # d3dx9.libをリンク
target_link_libraries(${TARGET_NAME} PUBLIC ${dinput8_lib}) # dinput8.libをリンク
target_link_libraries(${TARGET_NAME} PUBLIC ${xinput.lib}) # xinput.libをリンク
target_link_libraries(${TARGET_NAME} PUBLIC ${dxguid_lib}) # dxguid.libをリンク

target_link_libraries(${TARGET_NAME} PUBLIC xaudio2.lib) # XAudio2ライブラリをリンク
target_link_libraries(${TARGET_NAME} PUBLIC json11) # json11ライブラリをリンク

if(IMGUI)
	target_link_libraries(${TARGET_NAME} PUBLIC imgui)  # imguiをリンクする
endif()

# インクルードファイルのパスを追加する
target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include  
	${CMAKE_CURRENT_SOURCE_DIR}/3rdparty 
	${THIRD_PARTY_DIR}/d3d9/include  
)
