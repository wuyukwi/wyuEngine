#include "GameManager.h"
#include "WyuEngine.h"

GameManager::~GameManager()
= default;

void GameManager::Start()
{

    SceneManager::Start();

    // sceneの初期化
    m_menuScene = new MenuScene();
    m_gameScene = new GameScene();

    this->SetEnableScene(m_menuScene);

    m_SceneImguiEnable = true;
}

void GameManager::Tick(float delta)
{
#if IMGUI_ENABLE
    ImGui::Begin("SceneManager");

    ImGui::Text("EnableScene :%s", m_enableScene->GetSceneName().c_str());
    ImGui::Checkbox("SceneImguiEnable", &m_SceneImguiEnable);
    m_enableScene->SetImguiEnable(m_SceneImguiEnable);

    ImGui::Text(u8"---Sceneの切り替え--");
    if (ImGui::Button("GameScene"))
    {
        SetEnableScene(m_gameScene);
    }
    if (ImGui::Button("MenuScene"))
    {
        SetEnableScene(m_menuScene);
    }

    ImGui::End();
#endif

    if (m_enableScene->GetSceneName() == "MenuScene")
    {
        if (m_menuScene->GetNextScene() == "GameScene")
        {
            if (SetFade(FADE_IN, 1))
            {
                SetEnableScene(m_gameScene);
            }
        }
    }

    if (m_enableScene->GetSceneName() == "GameScene")
    {
        if (this->GetFadeMode() != FADE_NONE)
        {
            if (SetFade(FADE_OUT, 1))
            {

            }
        }

    }

    SceneManager::Tick(delta);

}

void GameManager::ShutDown()
{
    SceneManager::ShutDown();

    m_menuScene->ShutDown();
    SAFE_DELETE(m_menuScene)
        m_gameScene->ShutDown();
    SAFE_DELETE(m_gameScene)
}
