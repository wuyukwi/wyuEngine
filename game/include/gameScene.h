#pragma once

#include <string>
#include "Scene.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"

class GameScene :public Scene
{
public:
    ~GameScene() override;

    void Start() override;

    void Tick(float delta) override;

    void ShutDown() override;


private:
    void ProcessJsonFile(const std::string& file_name);

    std::map <std::string, Sprite*> m_spriteList{};

    std::vector<Enemy*>m_enemy;

    Player* m_player = nullptr;

    float m_time = 0.0f;
    int32_t m_timeCount = 0;
};


