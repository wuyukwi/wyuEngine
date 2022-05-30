/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-30 09:36:45
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-30 09:36:46
 * @FilePath: \wyuEngine\sources\Framework\Common\Engine.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "wyuEngine.hpp"

 // Parse command line, read configuration, initialize all sub modules
int ENGINE::wyuEngine::Initialize()
{
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

    return 0;
}


// Finalize all sub modules and clean up all runtime temporary files.
void ENGINE::wyuEngine::Finalize()
{
    g_pGPUManager->Finalize();
    g_pMemoryManager->Finalize();
    g_pApp->Finalize();
}


// One cycle of the main loop
void ENGINE::wyuEngine::Tick()
{
    while (!g_pApp->IsQuit()) {
        g_pApp->Tick();
        g_pMemoryManager->Tick();
        g_pGPUManager->Tick();
    }
}

