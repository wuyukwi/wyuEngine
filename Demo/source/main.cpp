/*********************************************************************************

  *FileName: main.cpp
			コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/02

**********************************************************************************/

//エンジンのインクルードは必須
#include "WyuEngine.h"

// 自分のゲームマネージャークラスは必須
#include "GameManager.h"

// ゲームエンジンのグローバルポインター
WyuEngine* g_pEngine = nullptr;

int main(int argc, char** argv)
{
	g_pEngine = new WyuEngine();
	SceneManager* scene_manager = new GameManager();

	// エンジンの初期化処理
	g_pEngine->InitializeEngine(scene_manager);

	// ゲームループ
	g_pEngine->Run();

	//　ゲーム終了
	g_pEngine->ShutdownEngine();

	return 0;
}


