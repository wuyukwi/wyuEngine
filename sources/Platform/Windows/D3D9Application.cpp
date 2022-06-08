#include "WindowsApplication.hpp"
#include "D3D9Renderer.hpp" 
#include "MemoryManager.hpp"

using namespace wyuEngine;

namespace wyuEngine {
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 4, 960, 540, false, ("Game Engine From Scratch (Windows DX9)"));
    IApplication* g_pApp = new WindowsApplication(config);
    RendererManager* g_pGPUManager = new D3D9Renderer;
    MemoryManager* g_pMemoryManager = new MemoryManager;

}
