#include "GameScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../BossScene/BossScene.h"

#include "../../BaseObject/Player/Player.h"

void GameScene::Draw()
{
	m_player->Draw();
}

void GameScene::Update()
{
	bool currentZKeyState = (GetAsyncKeyState('Z') & 0x8000);
	// 「前回は押されていなくて、今回は押されている」時だけ実行
	if (currentZKeyState && !m_prevZKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<BossScene>());
	}
	// 次のフレームのために現在の状態を保存
	m_prevZKey = currentZKeyState;


	bool currentXKeyState = (GetAsyncKeyState('X') & 0x8000);
	if (currentXKeyState && !m_prevXKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<GameoverScene>());
	}
	m_prevXKey = currentXKeyState;

	m_player->Update();
}

void GameScene::Init()
{
	m_player = std::make_shared<Player>();
}

void GameScene::Release()
{

}