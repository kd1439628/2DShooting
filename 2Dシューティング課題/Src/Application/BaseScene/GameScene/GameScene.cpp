#include "GameScene.h"
#include "../../BaseChara/Player/Player.h"
#include "../SceneManager.h"

void GameScene::Draw()
{
	m_player->Draw();
}

void GameScene::Update()
{
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
	m_player->Update();
}

void GameScene::Init()
{
	m_player = std::make_shared<Player>();
}

void GameScene::Release()
{

}