/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-27 09:29:13
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-27 09:29:57
 * @FilePath: \wyuEngine\Framework\Common\GPUManager.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include "IRuntimeModule.hpp"

namespace wyuEngine {
    class RendererManager : public IRuntimeModule
    {
    public:
        virtual ~RendererManager() override = default;

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual void Tick() override;
    };
}