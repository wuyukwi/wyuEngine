/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-27 09:23:44
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-27 09:23:44
 * @FilePath: \wyuEngine\RHI\opengl\openGLManager.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

 #pragma once
#include "GPUManager.hpp"

namespace ENGINE {
    class OpenGLManager : public GPUManager
    {
    public:
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();
    private:
    };
}

