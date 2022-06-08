/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-03 12:48:35
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-03 12:48:35
 * @FilePath: \wyuEngine\sources\Renderer\D3D9\D3D9RendererManager.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "D3D9Renderer.hpp"
#include "WindowsApplication.hpp"
#include "utility.hpp"

using namespace wyuEngine;

namespace wyuEngine
{
    //GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, ("Game Engine From Scratch (Windows DX9)"));
    //IApplication* g_pApp = new WindowsApplication(config);
    //RendererManager* g_pGPUManager = new D3D9Renderer;
    //MemoryManager* g_pMemoryManager = new MemoryManager;

    HRESULT D3D9Renderer::CreateD3D9Resources()
    {
        HRESULT hr;

        m_hwnd = dynamic_cast<WindowsApplication*>(g_pApp)->GetMainWindow();

        m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (!m_Direct3D)
        {
            hr = E_FAIL;
            return hr;
        }

        ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
        ZeroMemory(&m_d3ddm, sizeof(m_d3ddm));
        ZeroMemory(&m_caps, sizeof(m_caps));

        // 現在のディスプレイモードを取得
        if (FAILED(hr = m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_d3ddm)))
            return hr;

        if (FAILED(hr = m_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_caps)))
            return hr;

        DWORD processing = 0;

        if (m_caps.VertexProcessingCaps != 0)
            processing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
        else
            processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

        m_fullscreen = g_pApp->GetConfiguration().fullscreen;
        if (m_fullscreen)
        {
            m_d3dpp.FullScreen_RefreshRateInHz = m_d3ddm.RefreshRate;
            m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
        }
        else
            m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        m_d3dpp.Windowed = !m_fullscreen;
        m_d3dpp.BackBufferWidth = g_pApp->GetConfiguration().screenWidth;
        m_d3dpp.BackBufferHeight = g_pApp->GetConfiguration().screenHeight;
        m_d3dpp.hDeviceWindow = m_hwnd;
        m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        m_d3dpp.BackBufferFormat = m_d3ddm.Format;
        m_d3dpp.BackBufferCount = 1;
        m_d3dpp.EnableAutoDepthStencil = TRUE;
        m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        if (FAILED(hr = m_Direct3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_d3ddm.Format, true,
            static_cast<D3DMULTISAMPLE_TYPE>(g_pApp->GetConfiguration().msaaSamples), NULL)))
        {
            return hr;
        }
        else
        {
            m_d3dpp.MultiSampleType = static_cast<D3DMULTISAMPLE_TYPE>(g_pApp->GetConfiguration().msaaSamples);
        }

        if (FAILED(hr = m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd, processing, &m_d3dpp, &m_Device)))
            return hr;

        if (m_Device == nullptr)
        {
            hr = E_FAIL;
            return hr;
        }
        // レンダーステート設定
      //m_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
      //m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
      //SetTransparent(RenderState::TRANSPARENCY_ENABLE, TransperentState::SRCALPHA, TransperentState::INVDSTALPHA);
      //EnableMultiSaple(true);


      // テクスチャフィルターの設定

      // テクスチャステージステート
        m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
        m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
        m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

        //CalculateProjMatrix(D3DX_PI / 4, 0.1f, 10000);

        return hr;
    }


    //uint32_t D3D9Renderer::CreateD3D9FVF(uint32_t flags)
    //{
    //    uint32_t fvf = 0;

    //    switch (flags)
    //    {
    //    case GUI_FVF:
    //        fvf = D3DFVF_GUI;
    //        break;
    //    default:
    //        fvf = NULL;
    //        break;
    //    }

    //    return fvf;
    //}

    //HRESULT D3D9Renderer::CreateStaticBuffer(uint32_t verType, PrimType primType, uint32_t totalVerts, uint32_t totalIndices, uint32_t stride, void** data, uint32_t* indices, uint32_t* staticId)
    //{
    //    HRESULT hr;
    //    void* ptr;
    //    int index = m_numStaticBuffers;

    //    if (!m_staticBufferList)
    //    {
    //        m_staticBufferList = new stD3D9StaticBuffer[1];

    //        if (!m_staticBufferList)
    //        {
    //            hr = E_FAIL;
    //            return hr;
    //        }

    //    }
    //    else
    //    {
    //        stD3D9StaticBuffer* temp;
    //        temp = new stD3D9StaticBuffer[m_numStaticBuffers + 1];

    //        memcpy(temp, m_staticBufferList, sizeof(stD3D9StaticBuffer) * m_numStaticBuffers);

    //        delete[] m_staticBufferList;
    //        m_staticBufferList = temp;
    //    }

    //    m_staticBufferList[index].numVerts = totalVerts;
    //    m_staticBufferList[index].numIndices = totalIndices;
    //    m_staticBufferList[index].primType = primType;
    //    m_staticBufferList[index].stride = stride;
    //    m_staticBufferList[index].fvf = CreateD3DFVF(verType);

    //    if (totalIndices > 0)
    //    {
    //        if (FAILED(m_Device->CreateIndexBuffer(
    //            sizeof(size_t) * totalIndices,
    //            D3DUSAGE_WRITEONLY,
    //            D3DFMT_INDEX16,
    //            D3DPOOL_DEFAULT,
    //            &m_staticBufferList[index].ibPtr, NULL)))
    //        {
    //            return UGP_FAIL;
    //        };

    //        if (FAILED(m_staticBufferList[index].ibPtr->Lock(0, 0, (void**)&ptr, 0)))
    //            return UGP_FAIL;

    //        memcpy(ptr, indices, sizeof(size_t) * totalIndices);
    //        m_staticBufferList[index].ibPtr->Unlock();
    //    }
    //    else
    //    {
    //        m_staticBufferList[index].ibPtr = NULL;
    //    }

    //    if (FAILED(m_Device->CreateVertexBuffer(
    //        totalVerts * stride,
    //        D3DUSAGE_WRITEONLY,
    //        m_staticBufferList[index].fvf,
    //        D3DPOOL_DEFAULT,
    //        &m_staticBufferList[index].vbPtr, NULL)))
    //        return UGP_FAIL;

    //    if (FAILED(m_staticBufferList[index].vbPtr->Lock(0, 0, (void**)&ptr, 0)))
    //        return UGP_FAIL;

    //    memcpy(ptr, data, totalVerts * stride);
    //    m_staticBufferList[index].vbPtr->Unlock();


    //    *staticId = m_numStaticBuffers;
    //    m_numStaticBuffers++;

    //    return UGP_OK;
    //}

    int D3D9Renderer::Initialize()
    {
        int result = 0;

        result = static_cast<int>(CreateD3D9Resources());

        return result;
    }

    void D3D9Renderer::Finalize()
    {
        SAFE_RELEASE(m_Device);
        SAFE_RELEASE(m_Direct3D);
    }

    void D3D9Renderer::Tick()
    {

    }


}
