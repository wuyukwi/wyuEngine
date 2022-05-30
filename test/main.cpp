/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-29 20:24:39
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-29 20:24:39
 * @FilePath: \wyuEngine\test\main.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "main.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    auto pEngine = new wyuEngine;

    pEngine->Initialize();

    pEngine->Tick();

    pEngine->Finalize();
}
