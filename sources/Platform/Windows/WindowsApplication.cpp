#include "WindowsApplication.hpp"
#include <tchar.h>

using namespace wyuEngine;


int wyuEngine::WindowsApplication::Initialize()
{
    // first call base class initialization
    int ret = BaseApplication::Initialize();

    if (ret != 0)
        exit(ret);

    // get the HINSTANCE of the Console Program
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // ウインドウクラスの構造体の初期化
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);					// WNDCLASSEXのメモリサイズ
    wcex.style = CS_CLASSDC;							// ウインドウのスタイル
    wcex.lpfnWndProc = WindowProc;						    // ウインドウプロシージャ
    wcex.cbClsExtra = 0;								// ０にする (通常は使用しない)
    wcex.cbWndExtra = 0;								// ０にする (通常は使用しない)
    wcex.hInstance = hInstance;				// インスタンスハンドル
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// タスクバーのアイコン
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			// マウスカーソル
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// クライアント領域の背景色
    wcex.lpszMenuName = NULL;							// メニューバー
    wcex.lpszClassName = "GameEngineFromScratch";				// ウインドウクラスの名前
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wcex);

    // クライアント領域を指定のサイズに調整
    RECT rect = { 0, 0, static_cast<long>(m_Config.screenWidth),  static_cast<long>(m_Config.screenHeight) };		// 画面サイズの構造体
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

    HWND hwnd = CreateWindowEx(
        0,								// 拡張ウインドウスタイル
        "GameEngineFromScratch",		            // ウインドウスタイルの名前
        m_Config.appName,		            // ウインドウの名前
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// ウインドウスタイル
        0,					            // ウインドウの左上X座標
        0,					            // 　　〃　　の左上Y座標
        (rect.right - rect.left),		//幅
        (rect.bottom - rect.top),		//高さ
        NULL,							// 親ウインドウのハンドル
        NULL,							// メニューハンドルまたは子ウインドウID
        hInstance,				                // インスタンスハンドル
        this);							// ウインドウ作成データ



// ウィンドウの表示
    ShowWindow(hwnd, SW_SHOW);

    m_hWnd = hwnd;

    return ret;
}

void wyuEngine::WindowsApplication::Finalize()
{
}

void wyuEngine::WindowsApplication::Tick()
{
    // this struct holds Windows event messages
    MSG msg;

    // we use PeekMessage instead of GetMessage here
    // because we should not block the thread at anywhere
    // except the engine execution driver module 
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }
}

// this is the main message handler for the program
LRESULT CALLBACK wyuEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsApplication* pThis;
    if (message == WM_NCCREATE)
    {
        pThis = static_cast<WindowsApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

        SetLastError(0);
        if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    // sort through and find what code to run for the message given
    switch (message)
    {
    case WM_PAINT:
    {
        pThis->OnDraw();
    }
    break;

    case WM_KEYDOWN:
    {
        // we will replace this with input manager
        m_bQuit = true;
    }
    break;

    // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        m_bQuit = true;
        return 0;
    }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}

