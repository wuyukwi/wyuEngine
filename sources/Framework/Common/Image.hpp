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

namespace wyuEngine {

    typedef struct _Image {
        uint32_t Width;
        uint32_t Height;
        R8G8B8A8Unorm* data;
        uint32_t bitcount;
        uint32_t pitch;
        size_t  data_size;
    } Image;

}