#pragma once
#include "engine.h"

class WyuEngine
{
public:
	WyuEngine() = default;
	~WyuEngine() = default;

	/**
	 * \brief ゲームエンジン初期化関数
	 * \param scene_manager SceneManagerクラスのポインター
	 * \return 成功: True 失敗：False
	 */
	bool InitializeEngine(SceneManager* scene_manager);

	//エンジンの終了処理
	void ShutdownEngine();

	//エンジン起動関数、終了まではずっとループする。
	void Run() const;

	Timer* GetTimer() const;
	RenderInterface* GetRenderer() const;
	GfxConfiguration* GetConfig() const;
	ConfigManager* GetPathManager() const;
	CInputInterface* GetInput() const;
	SoundManagerInterface* GetSoundManager() const;
	WindowsApplication* GetWinapp()const;

private:

	ConfigManager* m_pConfigManager = nullptr; //パス管理クラス、configファイルから読み込む
	Timer* m_pTimer = nullptr;//タイマークラス
	SceneManager* m_pSceneManager = nullptr;//シンーマネージャー
	WindowsApplication* m_WinApp = nullptr;//ウィンドウズアプリケーションクラス
	RenderInterface* m_Renderer = nullptr;//描画全般管理するクラス
	CInputInterface* m_Input = nullptr;//inputマネージャー
	SoundManagerInterface* m_Sound = nullptr;//音声マネージャー
	GfxConfiguration* m_Config = nullptr;//設定保存用クラス

	int32_t m_arialID;       //フォントid
};

//グローバル変数
extern WyuEngine* g_pEngine;

