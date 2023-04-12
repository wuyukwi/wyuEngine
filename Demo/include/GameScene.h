#pragma once

#include <string>

#include "light.h"
#include "Scene.h"
#include "Node3D.h"

class GameScene :public Scene
{
public:
    ~GameScene() override;

    void Start() override;

    void Tick(float delta) override;

    void ShutDown() override;

private:
    std::map <std::string, Sprite*> m_ModelMap{};

    CameraNode* m_camera = nullptr;
    AnimationNode3D* m_ani3D = nullptr;
    TerrainNode* m_terrain = nullptr;
    stLight m_light{};

    float m_time = 0.0f;
    int32_t m_timeCount = 0;
};


