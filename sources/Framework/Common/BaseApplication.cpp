#include "BaseApplication.hpp"
#include <iostream>

using namespace wyuEngine;

bool wyuEngine::BaseApplication::m_bQuit = false;

wyuEngine::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
{
}

// Parse command line, read configuration, initialize all sub modules
int wyuEngine::BaseApplication::Initialize()
{
    std::cout << m_Config;

    return 0;
}


// Finalize all sub modules and clean up all runtime temporary files.
void wyuEngine::BaseApplication::Finalize()
{
}


// One cycle of the main loop
void wyuEngine::BaseApplication::Tick()
{
}

bool wyuEngine::BaseApplication::IsQuit()
{
    return m_bQuit;
}
