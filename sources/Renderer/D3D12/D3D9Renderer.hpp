/*********************************************************************************

  *FileName: D3D9Renderer.h
            コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/02

**********************************************************************************/

#ifndef _D3D_RENDERER_H_
#define _D3D_RENDERER_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "structs.h"
#include "RenderInterface.h"

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

struct stD3D9Texture
{
    stD3D9Texture() : fileName(0), image(0), width(0), height(0), enable(0) {}

    char* fileName;
    float width, height;
    bool enable;
    LPDIRECT3DTEXTURE9 image;
};

class CD3D9Renderer : public CRenderInterface
{
public:
    CD3D9Renderer();
    ~CD3D9Renderer();

    bool Initialize(int w, int h, bool fullScreen) override;

    void SetClearCol(float r, float g, float b, float a) override;
    void StartRender(bool bColor, bool bDepth, bool bStencil) override;
    void ClearBuffers(bool bColor, bool bDepth, bool bStencil) override;
    void EndRendering();

    int AddTexture2D(const char* file, int* texId) override;
    void ApplyTexture(size_t index, int texId) override;

    // スタティックバファ作成関数
    int CreateStaticBuffer(VertexType, PrimType,
        size_t totalVerts, size_t totalIndices,
        size_t stride, void** data, size_t* indices,
        int* staticId) override;

    int LoadUMFAsStaticBuffer(char* file, int meshIndex, int* staticID) override;
    int LoadUMFAsStaticBuffer(char* file, int meshIndex, int staticID) override;
    int LoadOBJAsStaticBuffer(char* file, int* staticID) override;
    int LoadOBJAsStaticBuffer(char* file, int staticID) override;
    int LoadXModel(char* file, int* xModelId) override;
    int LoadXModel(char* file, int xModelId) override;

    void ReleaseAllStaticBuffers() override;
    void ReleaseAllXModels() override;
    int ReleaseStaticBuffer(int staticID) override;
    int ReleaseXModel(int xModelId) override;

    int RenderStaticBuffer(int staticId) override;
    int RenderXModel(int xModelId) override;

    void GetXModelBoundingSphere(int xModelId, Vector3f* origin, float* radius)
    {
        if (xModelId < 0 || xModelId >= m_numXModels || !m_xModels)
            return;

        D3DXVECTOR3 center;
        float r;

        m_xModels[xModelId].GetBoundingSphere(&center, &r);

        if (origin)
        {
            origin->x = center.x;
            origin->y = center.y;
            origin->z = center.z;
        }

        if (radius)
            *radius = r;
    }

    void UpdateXAnimation(int xModelId, float time, Matrix4x4f* mat) override;


    void SetViewMatrix(Matrix4x4f* mat) override;
    void SetWorldMatrix(Matrix4x4f* mat) override;
    void GetProjectMatrix(Matrix4x4f* mat) override;
private:
    void OneTimeInit();


private:
    D3DXCOLOR m_Color;
    LPDIRECT3D9 m_Direct3D;
    LPDIRECT3DDEVICE9 m_Device;
    D3DDISPLAYMODE m_d3ddm;
    D3DPRESENT_PARAMETERS m_d3dpp;
    D3DCAPS9 m_caps;

    bool m_renderingScene;

    stD3D9StaticBuffer* m_staticBufferList;
    int m_numStaticBuffers;
    int m_activeStaticBuffer;

    stD3D9Texture* m_textureList;
    int m_numTextures;

    LPD3DXFONT* m_fonts;

    CXModel* m_xModels;

    int m_numXModels;

    D3DXMATRIX m_projection;
    D3DXMATRIX m_view;
};

bool CreateD3DRenderer(CRenderInterface** pObj);

#endif