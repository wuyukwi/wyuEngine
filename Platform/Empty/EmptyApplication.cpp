#include "BaseApplication.hpp"

namespace ENGINE {
    GfxConfiguration config;
    BaseApplication g_App(config);
    IApplication* g_pApp = &g_App;
}