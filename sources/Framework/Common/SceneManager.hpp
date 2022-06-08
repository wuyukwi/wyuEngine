/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-06 12:24:25
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-06 12:24:26
 * @FilePath: \wyuEngine\Sources\Framework\Common\SceneManager.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include "EngineMath.h"
#include "IRuntimeModule.hpp"
#include "SceneNode.hpp"
#include "SceneObject.hpp"

namespace wyuEngine
{
    class SceneManager :public IRuntimeModule
    {
    public:
        ~SceneManager() override;

        int Initialize() override;
        void Finalize() override;

        void Tick() override;

        void CreateScene(const char* name) const;

        //const BaseSceneNode& GetSceneForRendering() const;



    protected:
        //std::unique_ptr<BaseSceneNode> m_pScene;
    };
    extern SceneManager* g_pSceneManager;
}
