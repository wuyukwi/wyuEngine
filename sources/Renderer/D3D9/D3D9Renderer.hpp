/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-03 12:48:40
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-03 12:48:40
 * @FilePath: \wyuEngine\sources\Renderer\D3D9\D3D9RendererManager.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include <cstdint>
#include "RendererManager.hpp"
#include <d3d9.h>
#include <d3dx9.h>

namespace wyuEngine {
    class D3D9Renderer :public RendererManager
    {
    public:

        int Initialize() override;
        void Finalize() override;

        void Tick() override;

        // プリミティブタイプ
        enum class PrimType
        {
            NULL_TYPE,
            POINT_LIST,
            TRIANGLE_LIST,
            TRIANGLE_STRIP,
            TRIANGLE_FAN,
            LINE_LIST,
            LINE_STRIP
        };

        struct stD3D9StaticBuffer
        {
            stD3D9StaticBuffer() : vbPtr(0), ibPtr(0), numVerts(0),
                numIndices(0), stride(0), fvf(0),
                primType(PrimType::NULL_TYPE) {}

            LPDIRECT3DVERTEXBUFFER9 vbPtr;
            LPDIRECT3DINDEXBUFFER9 ibPtr;
            size_t numVerts;
            size_t numIndices;
            size_t stride;
            size_t fvf;
            PrimType primType;
        };

        //HRESULT CreateStaticBuffer(uint32_t verType,
        //    PrimType primType, uint32_t totalVerts,
        //    uint32_t totalIndices, uint32_t stride, void** data,
        //    uint32_t* indices, uint32_t* staticId);

        //uint32_t CreateD3D9FVF(uint32_t flags);

    private:
        HRESULT CreateD3D9Resources();

        HWND m_hwnd = nullptr;
        LPDIRECT3D9 m_Direct3D = nullptr;
        LPDIRECT3DDEVICE9 m_Device = nullptr;
        D3DDISPLAYMODE m_d3ddm;
        D3DPRESENT_PARAMETERS m_d3dpp;
        D3DCAPS9 m_caps;

        bool m_fullscreen = false;

        //stD3D9StaticBuffer* m_staticBufferList;
        //uint32_t m_numStaticBuffers;
        //uint32_t m_activeStaticBuffer;
    };

}
