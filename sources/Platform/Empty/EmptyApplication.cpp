#include "BaseApplication.hpp"
#include "RendererManager.hpp"
#include "MemoryManager.hpp"


namespace wyuEngine {
    GfxConfiguration config;
    IApplication* g_pApp = static_cast<IApplication*>(new BaseApplication(config));
    RendererManager* g_pGPUManager = static_cast<RendererManager*>(new RendererManager);
    MemoryManager* g_pMemoryManager = static_cast<MemoryManager*>(new MemoryManager);
}