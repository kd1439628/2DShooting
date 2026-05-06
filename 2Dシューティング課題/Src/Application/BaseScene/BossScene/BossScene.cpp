#include "BossScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../ClearScene/ClearScene.h"

#include "../../BaseObject/Player/Player.h"
#include "../../BaseObject/Enemies/Enemy.h"

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


	// 1. 全オブジェクトの更新
	for (int i = 0; i < m_objList.size(); ++i)
	{
		// プレイヤーだけは弾を追加するためにリストを渡す
		auto player = std::dynamic_pointer_cast<Player>(m_objList[i]);
		if (player) {
			player->Update(m_objList);
		}
		else {
			m_objList[i]->Update();
		}
	}

	// 2. 死んだオブジェクト（画面外に出た弾など）を一括削除 ★
	auto it = m_objList.begin();
	while (it != m_objList.end())
	{
		if ((*it)->IsAlive() == false) {
			it = m_objList.erase(it); // ここでメモリも自動解放される
		}
		else {
			++it;
		}
	}

}

void BossScene::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawLine(-100, -10, 100, 10);

	// 全オブジェクト（プレイヤーも弾も）を順番に描画するだけ！
	for (auto& obj : m_objList)
	{
		obj->Draw();
	}
}

void BossScene::Init()
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

void BossScene::Release()
{

}
