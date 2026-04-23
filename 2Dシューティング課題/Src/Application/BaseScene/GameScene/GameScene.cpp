#include "GameScene.h"
#include "../../BaseChara/Player/Player.h"

void GameScene::Draw()
{
	m_player->Draw();
}

void GameScene::Update()
{
	m_player->Update();
}

void GameScene::Init()
{
	m_player = std::make_shared<Player>();
}

void GameScene::Release()
{

}