#include "WindowsApplication.hpp"
#include <tchar.h>

using namespace wyuEngine;


int wyuEngine::WindowsApplication::Initialize()
{
    // first call base class initialization
    const int ret = BaseApplication::Initialize();

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

    // マウス位置初期化
    SetCursorPos(0, 0);

    m_hWnd = hwnd;

    return ret;
}

void wyuEngine::WindowsApplication::Finalize()
{
}

void wyuEngine::WindowsApplication::Tick()
{
    // ウィンドウズメッセージハンドル
    MSG msg;

    // メッセージループ
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        // 仮想メッセージを文字メッセージへ変換
        TranslateMessage(&msg);

        // ウィンドウプロシージャへメッセージを送信
        DispatchMessage(&msg);
    }
}

// メインメッセージハンドラー
LRESULT CALLBACK wyuEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsApplication* pThis;
    if (message == WM_NCCREATE)
    {
        // CREATESTRUCT構造体を取得
        pThis = static_cast<WindowsApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

        SetLastError(0);  //エラーコードの設定

        // ポインターサイズの設定(32/64ビット)
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

    // 並べ替えて、指定されたメッセージに対して実行するコードを見つけます
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

    // ウィンドウ破棄のメッセージ
    case WM_DESTROY:
    {
        // WM_QUITメッセージを送る
        PostQuitMessage(0);
        m_bQuit = true;
        return 0;
    }
    }

    // switchステートメントが処理しなかったメッセージを処理します
    return DefWindowProc(hWnd, message, wParam, lParam);
}

