#include "GameScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../BossScene/BossScene.h"

#include "../../BaseObject/Player/Player.h"
#include "../../BaseObject/Enemies/Enemy.h"

void GameScene::Draw()
{
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Draw();
	}
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



	//全オブジェクトの更新関数を呼ぶ
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Update();
	}
}

void GameScene::Init()
{
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();	//①インスタンスを生成
	//player->Init();							//②初期化
	m_objList.push_back(player);			//③リストへ追加

	// エネミー
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 10; ++i)
	{
		enemy = std::make_shared<Enemy>();	// ①インスタンスを生成
		//enemy->Init();						// ②初期化
		m_objList.push_back(enemy);			// ③リストへ追加
	}
}

void GameScene::Release()
{

}