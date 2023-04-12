#include "GameScene.h"
#include "WyuEngine.h"
#include "math/MathDefines.h"

std::string ConvertToANSILambda(const std::string& str);

GameScene::~GameScene()
= default;

void GameScene::Start()
{
    m_sceneName = "GameScene";
    m_time = 0.0f;

    // カメラの初期化処理
    m_camera = new CameraNode();
    m_camera->SetPos(Vector3f{ 40.0f,50.0f,-180.0f });
    this->AddChild(m_camera);

    //　モデルの初期化処理
    m_ani3D = new AnimationNode3D("model/man/man.x");
    this->AddChild(m_ani3D);

    //　地形の初期化処理
    m_terrain = new TerrainNode("gameScene/coastMountain64.raw", 64, 64, 10, 0.5f);
    m_terrain->SetTexture("test.png");
    m_ani3D->SetTranslation(Vector3f(0.f, -2000.f, 0.f));
    this->AddChild(m_terrain);

    //　ライトの初期化処理
    Vector3f dir(1.0f, -1.0f, 1.0f);
    Color col(1.0f, 1.0f, 1.0f, 1.0f);
    m_light.InitDirectionalLight(dir, col);
    g_pEngine->GetRenderer()->SetLight(m_light, 0);

    //　カメラの視野角を指定、fovy：視野角（垂直方向の角度）zn：ニアクリップ平面の距離　zf：ファークリップ平面の距離
    g_pEngine->GetRenderer()->CalculateProjMatrix(PI / 4, 10.0f, 10000.0f);

    Scene::Start();
}

void GameScene::Tick(float delta)
{
    auto* pInput = g_pEngine->GetInput();

    // コントローラースティックの座標を保存する
    Vector2f L_pos, R_pos;
    if(pInput->GetControllerIsUse())
    {
       const Vector2f L_pos = Vector2f{ (pInput->GetLeftStickPos().x) / 32767.0f,(pInput->GetLeftStickPos().y) / 32767.0f };
       const Vector2f  R_pos = Vector2f{ (pInput->GetRightStickPos().x) / 32767.0f,(pInput->GetRightStickPos().y) / 32767.0f };
    }

    // タイムの加算処理
    m_time += delta;
    static float timeCount = 0.0f;
    timeCount += delta;
    if (timeCount > 1.0f)
    {
        timeCount = 0.0f;
        m_timeCount++;
    }

    static float walkSpeed = 100.0f;
    static float rotSpeed = 0.5f;

#if IMGUI_ENABLE
    if (m_SceneImguiEnable)
    {
        ImGui::Begin("GameScene", &m_SceneImguiEnable, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("\tTIME :%.3f\t", m_time);
        ImGui::Text(u8"操作方法：WASD移動、RF上下移動、十字キー//マウス右クリック: 視点の移動");

        // ライトの設定
        static Color lightColor(1.0f, 1.0f, 1.0f, 1.0f);
        static Vector3f lightDir(1.0f, -1.0f, 1.0f);
        ImGui::ColorEdit4("light color", lightColor);
        ImGui::DragFloat3("light dir", lightDir,0.01f, -1.0f, 1.0f);
        m_light.InitDirectionalLight(lightDir, lightColor);
        g_pEngine->GetRenderer()->SetLight(m_light, 0);

        //　カメラの情報
        Vector3f look = m_camera->GetCameraLook();
        Vector3f pos = m_camera->GetCameraPos();
        Vector3f right = m_camera->GetCameraRight();
        Vector3f up = m_camera->GetCameraUp();

        ImGui::Text(u8"カメラの情報");
        ImGui::Text("Pos (X: %.3f, Y : %.3f, Z : %.3f)", pos.x, pos.y, pos.z);
        ImGui::Text("Look (X: %.3f, Y : %.3f, Z : %.3f)", look.x, look.y, look.z);
        ImGui::Text("Right (X: %.3f, Y : %.3f, Z : %.3f)", right.x, right.y, right.z);
        ImGui::Text("Up (X: %.3f, Y : %.3f, Z : %.3f)", up.x, up.y, up.z);
        // カメラの移動速度の調整
        ImGui::DragFloat("WalkSpeed", &walkSpeed, 1.f, 30.0f, 1000.0f);
        ImGui::DragFloat("RotSpeed", &rotSpeed, 0.1f, 0.0f, 5.0f);

        static bool renderTerrain = true;
        // ImGuiを使用してトグルボタンを作成する
        ImGui::Checkbox("RenderTerrain", &renderTerrain);
        // 物体のレンダリングを実行するかどうかを確認する
        if (renderTerrain)
        {
            // 物体をレンダリングする処理
            m_terrain->SetIsRender(true);
        }
        else
        {
            m_terrain->SetIsRender(false);
        }


        // モデル開く処理
        if (ImGui::Button(u8"モデル読み込み"))
        {
            OPENFILENAME ofn;

            char szFileName[MAX_PATH] = "";

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFilter = "X Files (*.x)\0*.x\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = "x";

            const std::string ansiInitialDir = ConvertToANSILambda(g_pEngine->GetPathManager()->GetAssetFolder() + "/model");
            ofn.lpstrInitialDir = ansiInitialDir.c_str();

            if(GetOpenFileName(&ofn))
            {
                m_ani3D->LoadModel(ofn.lpstrFile);
            }
        }

        // モデルの移動
        static Vector3f ts;
        ImGui::DragFloat3("Model Translation", ts,1.f, -10000.0f, 10000.0f);
        if (ImGui::Button("Reset Translation"))
        {
            ts = Vector3f(0, 0, 0);
        }
        m_ani3D->SetTranslation(ts);

        // モデルの回転
        static Vector3f rot;
        ImGui::DragFloat3("Model Rotation", rot, 0.01f,-1.0f, 1.0f);
        if (ImGui::Button("Reset Rotation"))
        {
            rot = Vector3f(0, 0, 0);
        }
        m_ani3D->SetRotation(rot);

        // モデルのスケーリング
        static float Scaling = 1.0f;
        ImGui::DragFloat("Model Scaling", &Scaling, 0.01f, -100.0f, 100.0f);
        if (ImGui::Button("Reset Scaling"))
        {
            Scaling = 1.0f;
        }
        m_ani3D->SetScaling(Scaling);

        ImGui::End();
    }
#endif

    float walk_speed = walkSpeed * delta;
    float rot_speed = rotSpeed * delta;

    //　キーボードのカメラ操作
    if (pInput->KeyDown(DIK_W))
        m_camera->walk(walk_speed);

    if (pInput->KeyDown(DIK_S))
        m_camera->walk(-walk_speed);

    if (pInput->KeyDown(DIK_A))
        m_camera->strafe(-walk_speed);
   
    if (pInput->KeyDown(DIK_D))
        m_camera->strafe(walk_speed);

    if (pInput->KeyDown(DIK_R))
        m_camera->fly(walk_speed);

    if (pInput->KeyDown(DIK_F))
        m_camera->fly(-walk_speed);

    if (pInput->KeyDown(DIK_UP))
        m_camera->pitch(rot_speed);

    if (pInput->KeyDown(DIK_DOWN))
        m_camera->pitch(-rot_speed);

    if (pInput->KeyDown(DIK_LEFT))
        m_camera->yaw(rot_speed);

    if (pInput->KeyDown(DIK_RIGHT))
        m_camera->yaw(-rot_speed);

    //　マウスのカメラ操作
    if(pInput->MouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        m_camera->yaw(pInput->GetMousePos(true).x * -delta);
        m_camera->pitch(pInput->GetMousePos(true).y * -delta);
    }

    Scene::Tick(delta);
}

void GameScene::ShutDown()
{

    Scene::ShutDown();
}

std::string ConvertToANSILambda(const std::string& str)
{
    // UTF-8からUnicode文字列に変換
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);

    // UnicodeからANSI文字列に変換
    len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string ansi(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &ansi[0], len, nullptr, nullptr);

    // パスの区切り文字をWindows用に変換
    std::replace(ansi.begin(), ansi.end(), '/', '\\');

    return ansi;
}
