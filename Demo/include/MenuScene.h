#pragma once

#include "Scene.h"

class MenuScene : public Scene
{
public:
    ~MenuScene() override;

    void Start() override;

    void Tick(float delta) override;

    void ShutDown() override;


private:
    SpriteBackGround* m_pBackGround = nullptr;
    SpriteButton* m_pStartButton = nullptr;
    SpriteButton* m_pExitButton = nullptr;

    SpriteAnim* m_pTestAnim = nullptr;

};

