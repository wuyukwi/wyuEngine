/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-06 12:24:30
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-06 12:24:31
 * @FilePath: \wyuEngine\Sources\Framework\Common\SceneManager.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "SceneManager.hpp"

using namespace wyuEngine;

SceneManager::~SceneManager()
{

}

int SceneManager::Initialize()
{
    int result = 0;

    return result;
}

void SceneManager::Finalize()
{

}

void SceneManager::Tick()
{

}

void SceneManager::CreateScene(const char* name)
{
    m_pScene->AppendChild(std::make_unique<BaseSceneNode>(BaseSceneNode(name)));
}

const BaseSceneNode& SceneManager::GetSceneForRendering()
{
    return *m_pScene;
}


