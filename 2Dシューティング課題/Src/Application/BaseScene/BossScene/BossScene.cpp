#include "BossScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../ClearScene/ClearScene.h"

#include "../../BaseObject/Player/Player.h"

void BossScene::Update()
{

	bool currentZKeyState = (GetAsyncKeyState('Z') & 0x8000);
	if (currentZKeyState && !m_prevZKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<ClearScene>());
	}
	m_prevZKey = currentZKeyState;


	bool currentXKeyState = (GetAsyncKeyState('X') & 0x8000);
	if (currentXKeyState && !m_prevXKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<GameoverScene>());
	}
	m_prevXKey = currentXKeyState;


	m_player->Update();

}

void BossScene::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawLine(-100, -10, 100, 10);

	m_player->Draw();
}

void BossScene::Init()
{
	m_player = std::make_shared<Player>();
}

void BossScene::Release()
{

}
