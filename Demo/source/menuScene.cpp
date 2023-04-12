#include "WyuEngine.h"
#include "json11.hpp"
#include "MenuScene.h"
#include "math/MathDefines.h"

MenuScene::~MenuScene()
{

}

void MenuScene::Start()
{
    // 画面遷移に使うためにSceneの名前を設定
    m_sceneName = "MenuScene";

    // 画面のサイズを取得
    const int32_t width = g_pEngine->GetConfig()->screenWidth;
    const int32_t height = g_pEngine->GetConfig()->screenHeight;

    // テクスチャのパスを渡して初期化する(テクスチャフォルダからの相対パス)
    m_pBackGround = new SpriteBackGround(0, "menu/title.png");
    m_pBackGround->SetSize(width, height);
    m_pBackGround->SetPos(width / 2, height / 2);
    this->AddChild(m_pBackGround);

    m_pStartButton = new SpriteButton(1, "menu/new_game.png");
    m_pStartButton->SetScalar(0.6f);
    m_pStartButton->SetPos(width - width / 8, height / 2 + height / 10);
    m_pStartButton->SetBounding(true);
    this->AddChild(m_pStartButton);

    m_pExitButton = new SpriteButton(1, "menu/exit_game.png");
    m_pExitButton->SetScalar(0.6f);
    m_pExitButton->SetPos(width - width / 8, height / 2 + height / 10 * 2);
    m_pExitButton->SetBounding(true);
    this->AddChild(m_pExitButton);

    m_pTestAnim = new SpriteAnim(1, "menu/test.png");
    m_pTestAnim->SetSize(370, 587);
    m_pTestAnim->SetScalar(0.3f);
    m_pTestAnim->SetPos(width / 2, height / 2);
    m_pTestAnim->AddAnimation("menu/test.png", Vector2i{ 10,5 }, "testAnim", Vector2i{ 0,10 }, Vector2i{ 0,5 }, 0.05f);
    m_pTestAnim->SetTextureFrames(Vector2i{ 0,0 });
    m_pTestAnim->SetBounding(true);
    m_pStartButton->AddChild(m_pTestAnim);

    // soundsフォルダから音声ファイルを読み込み
    g_pEngine->GetSoundManager()->LoadJsonFile("SoundList.json");
    g_pEngine->GetSoundManager()->Play("game_bgm");

    Scene::Start();
}

void MenuScene::Tick(float delta)
{
    //　マウスの位置をベクトルに保存する
    const Vector2f mouse_pos = Vector2f{ static_cast<float>(g_pEngine->GetInput()->GetMousePos().x)
        ,static_cast<float>(g_pEngine->GetInput()->GetMousePos().y) };

    //　マウスの位置をボタンに渡す
    m_pStartButton->SetMousePos(mouse_pos);
    m_pExitButton->SetMousePos(mouse_pos);

    static auto pInput = g_pEngine->GetInput();
    static float alpha = 1.0f;

#if IMGUI_ENABLE

    if (m_SceneImguiEnable)
    {
        ImGui::Begin("MenuScene", &m_SceneImguiEnable, ImGuiWindowFlags_AlwaysAutoResize);

        //　2Dアニメーションデモンストレーション
        static bool testAnimEnable = true;
        ImGui::Checkbox("AnimationTest", &testAnimEnable);
        if (testAnimEnable)
        {
            ImGui::Begin("AnimationTest", &testAnimEnable, ImGuiWindowFlags_AlwaysAutoResize);

            // windowのposを表示
            ImVec2 window_pos = ImGui::GetWindowPos();
            ImGui::SetWindowPos(ImVec2(window_pos.x, window_pos.y)); // ウィンドウの位置を左上に設定
            ImGui::Text("WindowPos x : %f , y: %f", window_pos.x, window_pos.y);

            // ZBufferの設定
            static float ZBuffer = 0.0f;
            ImGui::SliderFloat("ZBuffer", &ZBuffer, 0.f, 1.f);
            m_pTestAnim->SetZbuffer(ZBuffer);

            // アニメーション再生の設定
            static bool isPlaying = true;
            static float speed = 0.05f;
            ImGui::Checkbox("Playing", &isPlaying);
            ImGui::SameLine();
            ImGui::SliderFloat(u8"フレーム間隔", &speed,0.001f, 0.1f);
            if (isPlaying)
            {
                // 再生処理
                m_pTestAnim->PlayAnimation("testAnim", speed);
            }

            // Posの設定
            static Vector2f position = m_pTestAnim->GetPos(); 
            ImGui::Text("Position:");
            ImGui::SameLine();
            ImGui::DragFloat2("##position", &position.x);
            m_pTestAnim->SetPos(position);

            // スケールの設定
            static float Scalar = 1.0f;
            ImGui::SliderFloat("Scalar", &Scalar, 0.f, 5.f);
            m_pTestAnim->SetScalar(Scalar);

            //static bool isMouseInside = m_pTestAnim->isPointInside(mouse_pos);
            //ImGui::Text("isMouseInside: %s", isMouseInside ? "true" : "false");

            // ローテーションの設定
            static float rot = 0.f;
            ImGui::SliderFloat("rot", &rot, -PI, PI);
            m_pTestAnim->SetRot(rot);

            // 色の設定
            static Vector4f color = 1.0f;
            ImGui::ColorEdit4("color RGBA", &color[0]);
            m_pTestAnim->SetColor(color);

            ImGui::End();
        }


        // BGM音量設定
        static float volume = 0.0f;
        ImGui::SliderFloat("BGM volume", &volume, -50.0f, 40.0f);
        g_pEngine->GetSoundManager()->SetVolume(volume, "game_bgm");

        ImGui::End();
    }
#endif

    // ボタン選択した時の処理
    static bool fadeIn = true, fadeOut = false;
    static float fadeSpeed = 0.01f;

    if (fadeIn)
    {
        alpha += fadeSpeed;
        if (alpha >= 1.0f)
        {
            fadeIn = false;
            fadeOut = true;
        }
    }

    if (fadeOut)
    {
        alpha -= fadeSpeed;
        if (alpha <= 0.0f)
        {
            fadeOut = false;
            fadeIn = true;
        }
    }

    static int32_t Select = 0;

    // コントローラーの選択処理
    if (Select == 0)
    {
        m_pStartButton->SetColorAlpha(alpha);

        if (pInput->ControllerButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, 0, true) || pInput->KeyDown(DIK_S, true))
        {
            Select = 1;
            alpha = 1.0f;
            m_pStartButton->SetColorAlpha(1.0f);
        }
        else if (pInput->ControllerButtonDown(XINPUT_GAMEPAD_DPAD_UP, 0, true) || pInput->KeyDown(DIK_W, true))
        {
            Select = 1;
            alpha = 1.0f;
            m_pStartButton->SetColorAlpha(1.0f);
        }

        if (pInput->ControllerButtonDown(XINPUT_GAMEPAD_A, 0, true) || pInput->KeyDown(DIK_SPACE, true))
        {
            m_nextScene = "GameScene";
        }
    }
    else if (Select == 1)
    {
        m_pExitButton->SetColorAlpha(alpha);
        if (Select == 1 && pInput->ControllerButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, 0, true) || pInput->KeyDown(DIK_S, true))
        {
            Select = 0;
            alpha = 1.0f;
            m_pExitButton->SetColorAlpha(1.0f);
        }
        else if (Select == 1 && pInput->ControllerButtonDown(XINPUT_GAMEPAD_DPAD_UP, 0, true) || pInput->KeyDown(DIK_W, true))
        {
            Select = 0;
            alpha = 1.0f;
            m_pExitButton->SetColorAlpha(1.0f);
        }

        if (pInput->ControllerButtonDown(XINPUT_GAMEPAD_A, 0, true) || pInput->KeyDown(DIK_SPACE, true))
        {
            g_pEngine->GetWinapp()->Shutdown();
        }
    }


    //　マウスの選択処理
    if (m_pStartButton->IsMouseSelect())
    {
        m_pStartButton->SetColor(0, 0, 0);

        if (pInput->MouseButtonDown(MOUSE_LEFT_BUTTON, true))
        {
            m_nextScene = "GameScene";
        }
    }
    else
    {
        m_pStartButton->SetColor(255, 255, 255);
    }

    if (m_pExitButton->IsMouseSelect())
    {
        m_pExitButton->SetColor(0, 0, 0);
        if (g_pEngine->GetInput()->MouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            g_pEngine->GetWinapp()->Shutdown();
        }
    }
    else
    {
        m_pExitButton->SetColor(255, 255, 255);
    }


    Scene::Tick(delta);
}

void MenuScene::ShutDown()
{
    SAFE_DELETE(m_pBackGround)
    SAFE_DELETE(m_pStartButton)
    SAFE_DELETE(m_pExitButton)

    m_nextScene.clear();
    g_pEngine->GetSoundManager()->StopALL();
    Scene::ShutDown();
}


