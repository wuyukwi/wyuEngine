/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-27 09:52:15
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-27 09:52:15
 * @FilePath: \wyuEngine\RHI\opengl\OpenGLManager.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

 #include <cstdio>
#include "glad/glad.h"
#include "OpenGLManager.hpp"

using namespace ENGINE;

extern struct gladGLversionStruct GLVersion;

int ENGINE::OpenGLManager::Initialize()
{
    int result;

    result = gladLoadGL();
    if (!result) {
        printf("OpenGL load failed!\n");
        result = -1;
    } else {
        result = 0;
        printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);

        if (GLAD_GL_VERSION_3_0) {
            // Set the depth buffer to be entirely cleared to 1.0 values.
            glClearDepth(1.0f);

            // Enable depth testing.
            glEnable(GL_DEPTH_TEST);

            // Set the polygon winding to front facing for the left handed system.
            glFrontFace(GL_CW);

            // Enable back face culling.
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
    }

    return result;
}

void ENGINE::OpenGLManager::Finalize()
{
}

void ENGINE::OpenGLManager::Tick()
{
}
