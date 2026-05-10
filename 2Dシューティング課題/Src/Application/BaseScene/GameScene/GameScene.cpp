#include "GameScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../BossScene/BossScene.h"

#include "../../BaseObject/Player/Player.h"
#include "../../BaseObject/Enemies/Enemy.h"
#include "../../Stage/Stage.h"

void GameScene::Draw()
{
	if (m_stage) { m_stage->Draw(); }

	for (auto& obj : m_objList)
	{
		obj->Draw();
	}

	
}

void GameScene::Update()
{
	// ステージの更新
	if (m_stage) { m_stage->Update(); }

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



	// 1. 全オブジェクトの更新
	std::vector<std::shared_ptr<BaseObject>> updateList = m_objList;
	for (auto& obj : updateList)
	{
		// obj自体が有効か、かつ生存フラグが立っているか確認
		if (obj && obj->IsAlive())
		{
			obj->Update(m_objList);
		}
	}

	// --- 2. 当たり判定 ---
	if (m_hitChecker) {
		m_hitChecker->AllCollision(m_objList);
	}

	// --- 3. UIへのHP反映と回復実行 ---
	// リストからPlayerを見つけて、HP情報をUIに送る
	for (auto& obj : m_objList) {
		auto player = std::dynamic_pointer_cast<Player>(obj);
		if (player) {
			// もしHit側で1000点超えていたら回復させる
			// (今回はHit::CheckCollision内でplayerを見つけるのが大変なので
			// ここでスコア状況を見て回復させるのがスマートです)
		}
	}

	// --- 敵の出現管理 ---
	if (m_spawnTimer > 0)
	{
		m_spawnTimer--;
	}
	else
	{
		// 1. 画面内の現在の敵の数を数える
		int currentEnemies = 0;
		for (auto& obj : m_objList) {
			if (std::dynamic_pointer_cast<Enemy>(obj)) currentEnemies++;
		}

		// 2. 上限に達していなければ生成を試みる
		if (currentEnemies < m_maxEnemyCount)
		{
			auto newEnemy = std::make_shared<Enemy>();

			// 重なりチェック（最大5回リトライ）
			bool isOverlapping = false;
			for (int retry = 0; retry < 5; ++retry)
			{
				isOverlapping = false;
				// Enemy::Initでランダム座標が決まるので、それをチェック
				for (auto& obj : m_objList)
				{
					auto otherEnemy = std::dynamic_pointer_cast<Enemy>(obj);
					if (otherEnemy)
					{
						// 新しい敵と既存の敵の距離を計算（Vector3の距離）
						float dist = (newEnemy->GetPos() - otherEnemy->GetPos()).Length();
						if (dist < 150.0f) // 150px以内なら「重なっている」とみなす
						{
							isOverlapping = true;
							break;
						}
					}
				}

				if (!isOverlapping) break; // 重なっていなければループを抜ける

				// 重なっていたらInitを呼び直して座標を再抽選
				newEnemy->Relocate();
			}

			// 最終的に重なっていなければリストに追加
			if (!isOverlapping)
			{
				m_objList.push_back(newEnemy);
				// 次の出現までの待ち時間を設定（60フレーム = 1秒など）
				m_spawnTimer = 70 + rand() % 50;
			}
		}
	}

	//当たり判定の実行
	if (m_hitChecker)
	{
		m_hitChecker->AllCollision(m_objList);
	}

	// --- 2. 不要なオブジェクトの削除 (erase-removeイディオム) ---
	// 生存フラグが false のものを一括で削除します。
	auto it = m_objList.begin();
	while (it != m_objList.end())
	{
		// nullチェックを追加し、!IsAlive() のものを削除
		if (!(*it) || !(*it)->IsAlive())
		{
			it = m_objList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameScene::Init()
{
	m_stage = std::make_shared<Stage>();


	// 当たり判定にUIを教える
	m_hitChecker = std::make_unique<Hit>();

	// プレイヤー生成
	auto player = std::make_shared<Player>();
	m_objList.push_back(player);

	// 初期設定
	m_spawnTimer = 60;
	m_maxEnemyCount = 8;
}

void GameScene::Release()
{
	m_objList.clear();
}