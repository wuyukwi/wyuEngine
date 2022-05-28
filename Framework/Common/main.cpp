#include <cstdio>
#include "IApplication.hpp"
#include "GPUManager.hpp"
#include "MemoryManager.hpp"

using namespace ENGINE;

namespace ENGINE {
    extern IApplication* g_pApp;
    extern MemoryManager* g_pMemoryManager;
    extern GPUManager* g_pGPUManager;
}

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
