#pragma once

#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"

class GameManager :public SceneManager
{
public:

    // オーバーライドは必須です
    ~GameManager() override;
    void Start() override;
    void Tick(float delta) override;
    void ShutDown() override;

private:
    // Sceneは一つ以上が必要です
    MenuScene* m_menuScene = nullptr;
    GameScene* m_gameScene = nullptr;
};

