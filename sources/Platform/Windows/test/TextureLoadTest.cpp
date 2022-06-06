/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-01 10:18:28
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-01 10:18:30
 * @FilePath: \wyuEngine\sources\Platform\Windows\test\TextureLoadTest.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#include "AssetLoader.hpp"
 //#include "BMP.hpp"
#include "D2DRenderer.hpp"
#include "MemoryManager.hpp"
#include "WindowsApplication.hpp"
#include "utility.hpp"
#include <iostream>
#include <tchar.h>
#include "stb_image.h"

using namespace wyuEngine;
using namespace std;

namespace wyuEngine {
    class TestGraphicsManager : public D2DRenderer {
    public:
        //using D2DRenderer::D2DRenderer;
        void DrawBitmap(const Image image[], int32_t index);

    private:
        ID2D1Bitmap* m_pBitmap = nullptr;
    };

    class TestApplication : public WindowsApplication {
    public:
        using WindowsApplication::WindowsApplication;

        int Initialize() override;

        void OnDraw() override;

    private:
        Image m_Image[2];
    };
} // namespace My

namespace wyuEngine {
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 1920, 1080, "Texture Load Test (Windows)");
    IApplication* g_pApp = new TestApplication(config);
    RendererManager* g_pGPUManager = new TestGraphicsManager;
    MemoryManager* g_pMemoryManager = new MemoryManager;

} // namespace My

int TestApplication::Initialize() {

    const int result = WindowsApplication::Initialize();

    if (result == 0) {
        AssetLoader asset_loader;
        /*   BmpParser parser;
           Buffer buf = asset_loader.SyncOpenAndReadBinary("Textures/icelogo-color.bmp");

           m_Image[0] = parser.Parse(buf);

           buf = asset_loader.SyncOpenAndReadBinary("Textures/icelogo-normal.bmp");

           m_Image[1] = parser.Parse(buf);

           m_Image[0].data = (buf.m_pData, m_Image[0].Width, m_Image[0].Height)*/
           // asset_loader.SyncOpenAndReadImage("Textures/icelogo-color.bmp", m_Image[0]);
        //asset_loader.SyncOpenAndReadImage("Textures/icelogo-normal.bmp", m_Image[1]);
        asset_loader.SyncOpenAndReadImage("Textures/mao.png", m_Image[1]);
        asset_loader.SyncOpenAndReadImage("Textures/png.png", m_Image[0]);
    }

    return result;
}

void TestApplication::OnDraw() {
    dynamic_cast<TestGraphicsManager*>(g_pGPUManager)
        ->DrawBitmap(m_Image, 0);
    dynamic_cast<TestGraphicsManager*>(g_pGPUManager)
        ->DrawBitmap(m_Image, 1);
}

void TestGraphicsManager::DrawBitmap(const Image* image, int32_t index) {
    HRESULT hr;

    if (image[index].pBuffer->GetDataReadOnly() == nullptr)
        return;

    // start build GPU draw command
    m_pRenderTarget->BeginDraw();


    D2D1_BITMAP_PROPERTIES props;
    props.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
    props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    props.dpiX = 72.0f;
    props.dpiY = 72.0f;
    SAFE_RELEASE(&m_pBitmap);
    hr = m_pRenderTarget->CreateBitmap(
        D2D1::SizeU(image[index].Width, image[index].Height), image[index].pBuffer->GetDataReadOnly(),
        image[index].Width * 4, props, &m_pBitmap);

    D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
    D2D1_SIZE_F bmpSize = m_pBitmap->GetSize();

    D2D1_RECT_F source_rect = D2D1::RectF(0, 0, bmpSize.width, bmpSize.height);

    float aspect = bmpSize.width / bmpSize.height;
    float dest_height = rtSize.height;
    float dest_width = rtSize.height * aspect;

    D2D1_RECT_F dest_rect =
        D2D1::RectF(dest_width * index, 0, dest_width * (index + 1), dest_height);

    m_pRenderTarget->DrawBitmap(m_pBitmap, dest_rect, 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        source_rect);

    // end GPU draw command building
    m_pRenderTarget->EndDraw();
}
