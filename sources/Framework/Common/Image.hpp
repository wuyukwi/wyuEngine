/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-01 10:54:07
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-01 10:54:07
 * @FilePath: \wyuEngine\sources\Framework\Common\Image.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include "EngineMath.h"
#include "Buffer.hpp"

namespace wyuEngine {

    enum class EImagePixelFormat
    {
        // Supported by all formats except .hdr
        r8_unorm,
        rg8_unorm,
        rgb8_unorm,
        rgba8_unorm,

        // Supported only by .png
        r16_unorm,
        rg16_unorm,
        rgb16_unorm,
        rgba16_unorm,

        // Supported only by .hdr
        r32_float,
        rg32_float,
        rgb32_float,
        rgba32_float,
    };


    struct ImageDesc
    {
        //! The pixel format of the image.
        EImagePixelFormat format;
        //! The width of the image.
        uint32_t width;
        //! The height of the image.
        uint32_t height;
    };

    /*  typedef struct _Image {
          uint32_t Width;
          uint32_t Height;
          R8G8B8A8Unorm* data;
          uint32_t bitcount;
          uint32_t pitch;
          size_t  data_size;
      } Image;*/

    typedef struct _Image {
        uint32_t Width;
        uint32_t Height;
        uint32_t channels;
        Buffer* pBuffer;
    } Image;

}