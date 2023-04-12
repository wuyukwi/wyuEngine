#include <algorithm>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <random>

#include "GameScene.h"
#include "main.h"
#include "json11.hpp"

using namespace std;
using namespace json11;

GameScene::~GameScene()
= default;

void random(int a[], int n)
{
	srand(static_cast<uint32_t>(g_pEngine->GetTimer()->GetTime()));
	for (int32_t i = 0; i < n; i++)
	{
		const int32_t index = rand() % (n - i) + i;
		if (index != i)
		{
			const int32_t tmp = a[i];
			a[i] = a[index];
			a[index] = tmp;
		}
	}
}


void GameScene::Start()
{
	m_sceneName = "GameScene";
	m_time = 0.0f;

	// マップの読み込み
	ProcessJsonFile("level/level1.json");

	const float width = g_pEngine->GetConfig()->screenWidth / 4;
	const float height = g_pEngine->GetConfig()->screenHeight;
	m_player->SetScreenSize(width, width * 3, 0.0f, height);

	m_player->SetShootInterval(0.1f);
	m_player->SetPos(900, 1000);

	Scene::Start();
}

void GameScene::Tick(float delta)
{
	auto* pInput = g_pEngine->GetInput();

	const Vector2f L_pos = Vector2f{ static_cast<float>(pInput->GetLeftStickPos().x) / 32767.0f
		,static_cast<float>(pInput->GetLeftStickPos().y) / 32767.0f };
	const Vector2f R_pos = Vector2f{ static_cast<float>(pInput->GetRightStickPos().x) / 32767.0f
	  ,static_cast<float>(pInput->GetRightStickPos().y) / 32767.0f };

	m_time += delta;

#if IMGUI_ENABLE
	if (m_SceneImguiEnable)
	{
		ImGui::Begin("GameScene", &m_SceneImguiEnable, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("\tTIME :%.3f\t", m_time);
		ImGui::Text(u8"操作方法：WASD移動、スペース：弾の発射");

		ImGui::End();
	}
#endif

	m_player->PlayAnimation("none");

	//コントローラー使う場合
	if (pInput->GetControllerIsUse())
	{
		if (L_pos.x != 0.0f)
		{
			m_player->SetMove(L_pos.x * 500.0f * delta, 0.5f);
		}
		if (L_pos.y != 0.0f)
		{
			m_player->SetMove(L_pos.y * 500.0f * delta, 1.0f);
		}

		static float time = m_player->GetShootInterval();
		if (pInput->ControllerButtonDown(XINPUT_GAMEPAD_X))
		{
			time += delta;
			if (time >= m_player->GetShootInterval())
			{
				this->AddChild(BulletManager::CreateBullet(BulletUser::Player, BulletType::ThunderBall, m_player->GetPos()));
				time = 0.0f;
			}
		}
		else if (pInput->ControllerButtonUp(XINPUT_GAMEPAD_X))
		{
			time = m_player->GetShootInterval();
		}
	}
	//キーボード使う場合
	else
	{
		if (pInput->KeyDown(DIK_A))
		{
			m_player->SetMove(500.0f * delta, -0.5f);
		}
		else if (pInput->KeyDown(DIK_D))
		{
			m_player->SetMove(500.0f * delta, 0.5f);
		}

		if (pInput->KeyDown(DIK_W))
		{
			m_player->SetMove(500.0f * delta, 1.0f);
		}
		else if (pInput->KeyDown(DIK_S))
		{
			m_player->SetMove(500.0f * delta, 0.0f);
		}

		static float time = m_player->GetShootInterval();
		if (pInput->KeyDown(DIK_SPACE))
		{
			time += delta;
			if (time >= m_player->GetShootInterval())
			{
				this->AddChild(BulletManager::CreateBullet(BulletUser::Player, BulletType::ThunderBall, m_player->GetPos()));
				time = 0.0f;
			}
		}
		else if (pInput->KeyUp(DIK_SPACE))
		{
			time = m_player->GetShootInterval();
		}
	}

	// 3秒ごとにenemyを生成します
	static float lastExecuteTime = 0.0f;
	lastExecuteTime += delta;

	if (lastExecuteTime >= 3.0f)
	{
		// ランダムエンジンの初期化
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		// 整数をランダムに生成
		const float width = g_pEngine->GetConfig()->screenWidth / 4;
		std::uniform_int_distribution<> dist(width, width * 3);
        const float rand_num = dist(engine);

		if (const auto enemy = EnemyManager::CreateEnemy(EnemyType::DEATH, Vector2f{ rand_num,0 }))
		{
			m_enemy.push_back(enemy);
			this->AddChild(enemy);
		}

		lastExecuteTime = 0.0f;
	}


	BulletManager::Tick(delta);
	EnemyManager::Tick(delta, m_enemy);
	Scene::Tick(delta);
}

void GameScene::ShutDown()
{
	if (!m_spriteList.empty())
	{
		for (auto& i : m_spriteList)
		{
			SAFE_DELETE(i.second)
		}
	}
	m_spriteList.clear();

	Scene::ShutDown();
}


void GameScene::ProcessJsonFile(const std::string& file_name)
{
	const auto width = g_pEngine->GetConfig()->screenWidth;
	const auto height = g_pEngine->GetConfig()->screenHeight;

	// stringにjsonファイルを読み込む
	std::ifstream asset_json_file(g_pEngine->GetPathManager()->GetFileFullPath(file_name));
	if (!asset_json_file)
	{
		cout << "!asset_json_file" << endl;
	}

	std::stringstream buffer;
	buffer << asset_json_file.rdbuf();
	std::string asset_json_text(buffer.str());

	//    cout << asset_json_text << endl;

	// jsonオブジェクトに解析し
	std::string error;
	auto&& json = Json::parse(asset_json_text, error);
	if (!error.empty())
	{
		cout << error << endl;
	}

	if (!json["node"].is_null())
	{
		// cout << json["node"].dump() << endl;
		for (auto& i : json["node"].array_items())
		{
			if (i["type"].string_value() == "SpriteBackGround")
			{
				auto node = new SpriteBackGround(i["texture"].int_value(), i["texture"].string_value());
				m_spriteList.insert({ i["name"].string_value(),node });
				this->AddChild(node);

				if (!i["size"].is_null())
				{
					node->SetSize(width / i["size"]["x"].int_value(), height / i["size"]["y"].int_value());
				}
				if (!i["scalar"].is_null())
				{
					node->SetScalar(i["scalar"].number_value());
				}
				if (!i["pos"].is_null())
				{
					node->SetPos(width / i["pos"]["x"].int_value(), height / i["pos"]["y"].int_value());
				}

				if (!i["rollSpeed"].is_null())
				{
					node->SetRollSpeed(i["rollSpeed"]["u"].number_value(), i["rollSpeed"]["v"].number_value());
				}
			}

			//}

			if (i["type"].string_value() == "player")
			{
				auto node = new Player(i["texture"].int_value(), i["texture"].string_value());
				m_player = node;
				// m_spriteList.insert({ i["name"].string_value(),node });
				this->AddChild(node);

				if (!i["size"].is_null())
				{
					node->SetSize(width / i["size"]["x"].int_value(), height / i["size"]["y"].int_value());
				}
				if (!i["scalar"].is_null())
				{
					node->SetScalar(i["scalar"].number_value());
				}
				if (!i["pos"].is_null())
				{
					node->SetPos(width / i["pos"]["x"].int_value(), height / i["pos"]["y"].int_value());
				}
				if (!i["animation"].is_null())
				{
					node->AddAnimation(
						i["animation"]["texture"].string_value(),
						Vector2i{ i["animation"]["frame"]["u"].int_value(),i["animation"]["frame"]["v"].int_value() },
						i["animation"]["name"].string_value(),
						Vector2i{ i["animation"]["frameX"]["begin"].int_value(),i["animation"]["frameX"]["end"].int_value() },
						Vector2i{ i["animation"]["frameY"]["begin"].int_value(),i["animation"]["frameY"]["end"].int_value() },
						i["animation"]["frameRate"].number_value()
					);
				}

			}

		}
	}
}