#pragma once

#include "IApplication.hpp"
#include "GfxConfiguration.h"
#include "RendererManager.hpp"
#include "MemoryManager.hpp"


namespace wyuEngine {
    extern IApplication* g_pApp;
    extern MemoryManager* g_pMemoryManager;
    extern RendererManager* g_pGPUManager;
}

namespace wyuEngine {
    class BaseApplication : public IApplication
    {
    public:
        BaseApplication(GfxConfiguration& cfg);
        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick();

        virtual bool IsQuit();

        inline GfxConfiguration& GetConfiguration() { return m_Config; };

    protected:
        virtual void OnDraw() {};

        // Flag if need quit the main loop of the application
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        // デフォルトの構成使用しないで強制に構成する
        BaseApplication() {};
    };
}
