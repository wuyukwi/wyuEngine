#include <objbase.h>
#include "D2DRenderer.hpp"
#include "WindowsApplication.hpp"
#include "utility.hpp"

using namespace wyuEngine;


namespace wyuEngine {
    extern IApplication* g_pApp;
}

HRESULT D2DRenderer::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

    HWND hWnd = reinterpret_cast<WindowsApplication*>(g_pApp)->GetMainWindow();

    if (m_pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        const D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left,
            rc.bottom - rc.top);

        hr = m_pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &m_pRenderTarget);
    }

    return hr;
}

int  D2DRenderer::Initialize()
{
    int result = 0;

    // initialize COM
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) return -1;

    if (FAILED(D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
        return -1;

    result = static_cast<int>(CreateGraphicsResources());

    return result;
}

void D2DRenderer::Tick()
{
}

void D2DRenderer::Finalize()
{
    SAFE_RELEASE(&m_pRenderTarget);
    SAFE_RELEASE(&m_pFactory);

    CoUninitialize();
}

