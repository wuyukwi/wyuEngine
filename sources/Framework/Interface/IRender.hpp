/*********************************************************************************

  *FileName: RenderInterface.h
            コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/02

**********************************************************************************/


#ifndef _RENDERINTERFACE_H_
#define _RENDERINTERFACE_H_

#include "defines.h"

namespace ENGINE {
    class CRenderInterface
    {
    public:
        CRenderInterface() : m_screenWidth(0), m_screenHeight(0), m_fullscreen(0) { }
        virtual ~CRenderInterface() {}

        virtual bool Initialize(int w, int h, bool fullScreen) = 0;
        virtual void OneTimeInit() = 0;

        virtual void SetClearCol(float r, float g, float b, float a) = 0;

        virtual void StartRender(bool bColor, bool bDepth, bool bStencil) = 0;
        virtual void ClearBuffers(bool bColor, bool bDepth, bool bStencil) = 0;
        virtual void EndRendering() = 0;

        virtual int AddTexture2D(const char* file, int* texId) = 0;
        virtual void SetMultiTexture() = 0;
        virtual void SetDetailMapping() = 0;
        virtual void ApplyTexture(size_t index, int texId) = 0;

        virtual void ReleaseAllStaticBuffers() = 0;
        virtual int ReleaseStaticBuffer(int staticID) = 0;

        virtual int RenderStaticBuffer(int staticId) = 0;

    protected:
        int m_screenWidth;
        int m_screenHeight;
        bool m_fullscreen;
    };
}
#endif