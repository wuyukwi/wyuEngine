/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-30 11:09:37
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-30 11:09:37
 * @FilePath: \wyuEngine\sources\Framework\Common\main.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#include "GPUManager.hpp"
#include "IApplication.hpp"
#include "MemoryManager.hpp"
#include <cstdio>

using namespace wyuEngine;

namespace wyuEngine {
    extern IApplication* g_pApp;
    extern MemoryManager* g_pMemoryManager;
    extern GPUManager* g_pGPUManager;
} // namespace wyuEngine

int main(int argc, char** argv) {
    int ret;

    if ((ret = g_pApp->Initialize()) != 0) {
        printf("App Initialize failed, will exit now.");
        return ret;
    }

    if ((ret = g_pMemoryManager->Initialize()) != 0) {
        printf("Memory Manager Initialize failed, will exit now.");
        return ret;
    }

    if ((ret = g_pGPUManager->Initialize()) != 0) {
        printf("Graphics Manager Initialize failed, will exit now.");
        return ret;
    }

    while (!g_pApp->IsQuit()) {
        g_pApp->Tick();
        g_pMemoryManager->Tick();
        g_pGPUManager->Tick();
    }

    g_pGPUManager->Finalize();
    g_pMemoryManager->Finalize();
    g_pApp->Finalize();

    return 0;
}