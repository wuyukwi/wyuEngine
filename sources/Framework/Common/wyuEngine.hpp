/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-30 09:37:27
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-30 09:37:28
 * @FilePath: \wyuEngine\sources\Framework\Common\Engine.h
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#include <cstdio>
#include "IApplication.hpp"
#include "GPUManager.hpp"
#include "MemoryManager.hpp"

using namespace ENGINE;

namespace ENGINE {
    extern IApplication* g_pApp;
    extern MemoryManager* g_pMemoryManager;
    extern GPUManager* g_pGPUManager;

    class wyuEngine :public IRuntimeModule
    {
    public:
        virtual ~wyuEngine() {};

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();
    };
}
