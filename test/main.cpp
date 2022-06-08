/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-29 20:24:39
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-29 20:24:39
 * @FilePath: \wyuEngine\test\main.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "main.h"
#include "D3D9Renderer.hpp"

using namespace wyuEngine;

namespace wyuEngine
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, false, ("Game Engine From Scratch (TestWindows DX9)"));
    IApplication* g_pApp = new TestApp(config);
    RendererManager* g_pGPUManager = new D3D9Renderer;
    MemoryManager* g_pMemoryManager = new MemoryManager;
    SceneManager* g_pSceneManager = new SceneManager;
}

int TestApp::Initialize()
{
    const int result = WindowsApplication::Initialize();

    if (result != 0)
        return result;


    return result;
}

void TestApp::Finalize()
{
    WindowsApplication::Finalize();

}

void TestApp::Tick()
{
    WindowsApplication::Tick();

}




