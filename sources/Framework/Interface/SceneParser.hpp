/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-07 11:29:52
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-07 11:29:52
 * @FilePath: \wyuEngine\sources\Framework\Interface\SceneParser.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include <memory>
#include <string>
#include <map>
#include "Interface.hpp"
#include "SceneNode.hpp"
#include "SceneObject.hpp"

namespace wyuEngine
{
    class Scene
    {
    public:
        Scene(const char* scene_name) :SceneGraph(new BaseSceneNode(scene_name))
        {
        }

        std::unique_ptr<BaseSceneNode> SceneGraph;
    };
}
