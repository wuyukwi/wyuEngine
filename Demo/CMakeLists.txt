set(TARGET_NAME "Demo")  # プロジェクト名を設定する
set(DEPLOY_CONFIG_DIR "configs/deployment")  # デプロイメント設定ファイルが存在する場所のパス
set(DEVELOP_CONFIG_DIR "configs/development")  # 開発設定ファイルが存在する場所のパス
file(GLOB GAME_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)  # ゲームのヘッダーファイルを検索する
file(GLOB GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)  # ゲームのソースファイルを検索する

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GAME_HEADERS} ${GAME_SOURCES})  # ファイルのソースグループを設定する

#set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS" )

add_executable(${TARGET_NAME} ${GAME_HEADERS} ${GAME_SOURCES})  # ゲームの実行ファイルを追加する

target_link_libraries(${TARGET_NAME} Engine)  # ゲームの実行ファイルに必要なライブラリをリンクする
target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)  # ゲームの実行ファイルで使用するヘッダーファイルが存在する場所のパス

set(BINARY_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")  # ゲームの実行ファイルの出力先のパス

set(POST_BUILD_COMMANDS
  COMMAND ${CMAKE_COMMAND} -E make_directory "${BINARY_ROOT_DIR}"  # 出力先のフォルダがなければ作成する
  COMMAND ${CMAKE_COMMAND} -E copy_directory "$<TARGET_FILE_DIR:${TARGET_NAME}>/" "${BINARY_ROOT_DIR}"  # ゲームの実行ファイルを出力先にコピーする
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${DEPLOY_CONFIG_DIR}/setting.ini" "${BINARY_ROOT_DIR}"  # デプロイメント設定ファイルを出力先にコピーする
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${DEVELOP_CONFIG_DIR}/setting.ini" "$<TARGET_FILE_DIR:${TARGET_NAME}>/"  # 開発設定ファイルをゲームの実行ファイルがあるフォルダにコピーする
)
add_compile_definitions(GAME_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")  # ゲームのルートフォルダのパスを定義する
add_compile_definitions(GAME_NAME="${TARGET_NAME}")  # ゲームの名前を定義する

add_custom_command(TARGET ${TARGET_NAME} ${POST_BUILD_COMMANDS})  # ゲームの実行ファイルが出力された後に実行するコマンドを設定する
