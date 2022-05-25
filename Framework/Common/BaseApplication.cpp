#include "BaseApplication.hpp"
#include <iostream>

using namespace ENGINE;

bool ENGINE::BaseApplication::m_bQuit = false;

ENGINE::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
{
}

// Parse command line, read configuration, initialize all sub modules
int ENGINE::BaseApplication::Initialize()
{
    std::cout << m_Config;

    return 0;
}


// Finalize all sub modules and clean up all runtime temporary files.
void ENGINE::BaseApplication::Finalize()
{
}


// One cycle of the main loop
void ENGINE::BaseApplication::Tick()
{
}

bool ENGINE::BaseApplication::IsQuit()
{
    return m_bQuit;
}
