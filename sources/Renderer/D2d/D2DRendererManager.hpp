/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-01 10:17:10
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-01 10:17:14
 * @FilePath: \wyuEngine\sources\Renderer\D2d\D2dGraphicsManager.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#pragma once
#include "RendererManager.hpp"
#include <d2d1.h>

namespace wyuEngine {
    class D2DRendererManager : public RendererManager {
    public:
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

    protected:
        HRESULT CreateGraphicsResources();

    protected:
        ID2D1Factory* m_pFactory = nullptr;
        ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
    };
} // namespace wyuEngine
