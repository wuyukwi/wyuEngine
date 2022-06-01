/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-24 13:06:13
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-25 15:31:15
 * @FilePath: \wyuEngine\Platform\Windows\WindowsApplication.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#pragma once

#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.hpp"


namespace wyuEngine {

    class WindowsApplication : public BaseApplication {
    public:
        WindowsApplication(GfxConfiguration& config) : BaseApplication(config) {}

        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick();

        inline HWND GetMainWindow() const { return m_hWnd; };

    private:
        // the WindowProc function prototype
        static LRESULT CALLBACK WindowProc(HWND hWnd,
            UINT message,
            WPARAM wParam,
            LPARAM lParam);

        HWND m_hWnd;
    };

};// namespace wyuEngine