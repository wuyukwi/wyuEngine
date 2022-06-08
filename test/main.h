/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-30 09:54:48
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-30 09:54:48
 * @FilePath: \wyuEngine\test\main.h
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include "Engine.h"


class TestApp : public wyuEngine::WindowsApplication
{
public:
    TestApp(wyuEngine::GfxConfiguration& config) : wyuEngine::WindowsApplication(config) {}
    //virtual ~TestApp() override = default;

    virtual int Initialize() override;
    virtual void Finalize() override;

    virtual void Tick() override;
};



#endif    // __MAIN_H__