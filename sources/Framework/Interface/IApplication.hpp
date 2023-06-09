﻿#pragma once

#include "IRuntimeModule.hpp"
#include "GfxConfiguration.h"

namespace wyuEngine {
    class IApplication : public IRuntimeModule
    {
    public:
        virtual int Initialize() override = 0;
        virtual void Finalize() override = 0;
        // One cycle of the main loop
        virtual void Tick() override = 0;

        virtual bool IsQuit() = 0;

        virtual GfxConfiguration& GetConfiguration() = 0;
    };
}

