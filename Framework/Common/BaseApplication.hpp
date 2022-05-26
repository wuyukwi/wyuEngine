#pragma once

#include "IApplication.hpp"
#include "GfxConfiguration.h"

namespace ENGINE {
    class BaseApplication : public IApplication
    {
    public:
        BaseApplication(GfxConfiguration& cfg);
        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick();

        virtual bool IsQuit();

    protected:
        // Flag if need quit the main loop of the application
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        // デフォルトの構成使用しないで強制に構成する
        BaseApplication() {};
    };
}
