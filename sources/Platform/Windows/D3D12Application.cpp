/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-27 16:57:59
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-27 16:57:59
 * @FilePath: \wyuEngine\Platform\Windows\D3D12Application.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "WindowsApplication.hpp"
#include "D3D12Renderer.hpp" 
#include "MemoryManager.hpp"
#include <tchar.h>

using namespace wyuEngine;

namespace wyuEngine {
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, _T("Game Engine From Scratch (Windows DX12)"));
    IApplication* g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
    RendererManager* g_pGPUManager = static_cast<RendererManager*>(new D3D12Renderer);
    MemoryManager* g_pMemoryManager = static_cast<MemoryManager*>(new MemoryManager);

}
