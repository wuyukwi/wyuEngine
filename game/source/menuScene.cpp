#include "main.h"
#include "json11.hpp"

MenuScene::~MenuScene()
{

}

void MenuScene::Start()
{
    m_sceneName = "MenuScene";

    const auto width = g_pEngine->GetConfig()->screenWidth;
    const auto height = g_pEngine->GetConfig()->screenHeight;

    m_pBackGround = new SpriteButton(0, "menu/title.png");
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

    g_pEngine->GetSoundManager()->Play("0");

    Scene::Start();
}

void MenuScene::Tick(float delta)
{
    const Vector2f mouse_pos = Vector2f{ static_cast<float>(g_pEngine->GetInput()->GetMousePos().x)
        ,static_cast<float>(g_pEngine->GetInput()->GetMousePos().y) };

    m_pStartButton->SetMousePos(mouse_pos);
    m_pExitButton->SetMousePos(mouse_pos);

    static auto pInput = g_pEngine->GetInput();
    static float alpha = 1.0f;

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
    SAFE_DELETE(m_pSettingButton)
    SAFE_DELETE(m_pExitButton)
    SAFE_DELETE(test)

    g_pEngine->GetSoundManager()->Stop("0");
    Scene::ShutDown();
}


