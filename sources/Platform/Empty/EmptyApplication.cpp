#include "BaseApplication.hpp"
#include "GPUManager.hpp"
#include "MemoryManager.hpp"


namespace ENGINE {
    GfxConfiguration config;
    IApplication* g_pApp = static_cast<IApplication*>(new BaseApplication(config));
    GPUManager* g_pGPUManager = static_cast<GPUManager*>(new GPUManager);
    MemoryManager* g_pMemoryManager = static_cast<MemoryManager*>(new MemoryManager);
}