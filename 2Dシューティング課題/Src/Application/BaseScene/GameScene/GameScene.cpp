#include "GameScene.h"
#include "../SceneManager.h"
#include "../GameoverScene/GameoverScene.h"
#include "../BossScene/BossScene.h"

#include "../../BaseObject/Player/Player.h"
#include "../../BaseObject/Enemies/Enemy.h"
#include "../../Stage/GameStage/Stage.h"
#include "../../BaseObject/Explosion/Explosion.h"

void GameScene::Draw()
{
	if (m_stage) { m_stage->Draw(); }

	// キャラクター・弾などの通常の描画
	for (auto& obj : m_objList)
	{
		obj->Draw();
	}

	if (m_ui) { m_ui->Draw(); }
}

void GameScene::Update()
{
	m_sceneTimer++;

	// 3分(180秒) ＋ 余韻(2秒) ＝ 10920フレーム経過したら終了
	if (m_sceneTimer >= 10920)
	{
		// 1. 現在のスコアをUIから取得する
		unsigned long finalScore = 0;
		if (m_ui)
		{
			finalScore = m_ui->GetScore();
		}

		// 2.ボス戦ではなく、スコアを表示するシーン（GameoverScene）へ遷移する
		// 引数に取得したスコアを渡すことで、画面に最終結果が表示されます
		SceneManager::Instance().SetNextScene(std::make_shared<GameoverScene>(finalScore));

		return; // 以降の更新処理を中断
	}

	std::shared_ptr<Player> playerPtr = nullptr;
	for (auto& obj : m_objList)
	{
		auto p = std::dynamic_pointer_cast<Player>(obj);
		if (p)
		{
			playerPtr = p;
			break;
		}
	}

	// プレイヤーがリストにいない、または死亡フラグが立っていたらゲームオーバー
	if (!playerPtr || !playerPtr->IsAlive())
	{
		// ★ タイマーを減らす
		m_gameoverTimer--;

		// ★ タイマーが0になったらシーンを切り替える
		if (m_gameoverTimer <= 0)
		{
			unsigned long finalScore = 0;
			if (m_ui)
			{
				finalScore = m_ui->GetScore();
			}
			SceneManager::Instance().SetNextScene(std::make_shared<GameoverScene>(finalScore, m_sceneTimer, 0));
		}
	}

	// ステージの更新
	if (m_stage) { m_stage->Update(); }

	//  全オブジェクトの更新
	std::vector<std::shared_ptr<BaseObject>> updateList = m_objList;
	for (auto& obj : updateList)
	{
		// obj自体が有効か、かつ生存フラグが立っているか確認
		if (obj && obj->IsAlive())
		{
			obj->Update(m_objList);
		}
	}

	// ---  当たり判定 ---
	if (m_hitChecker)
	{
		m_hitChecker->AllCollision(m_objList);
	}

	if (m_ui) { m_ui->Update(); }

	//bool currentZKeyState = (GetAsyncKeyState('Z') & 0x8000);
	//// 「前回は押されていなくて、今回は押されている」時だけ実行
	//if (currentZKeyState && !m_prevZKey)
	//{
	//	SceneManager::Instance().SetNextScene(std::make_shared<BossScene>());
	//}
	//// 次のフレームのために現在の状態を保存
	//m_prevZKey = currentZKeyState;


	bool currentXKeyState = (GetAsyncKeyState('X') & 0x8000);
	if (currentXKeyState && !m_prevXKey)
	{
		// UIから現在のスコアを取得
		unsigned long currentScore = 0;
		if (m_ui)
		{
			currentScore = m_ui->GetScore();
		}

		// GameoverScene に「現在のスコア」と「現在の経過時間(m_sceneTimer)」を渡して遷移する
		// （第3引数は被弾回数ですが、今回はとりあえず 0 を渡しています）
		SceneManager::Instance().SetNextScene(std::make_shared<GameoverScene>(currentScore, m_sceneTimer, 0));
	}
	m_prevXKey = currentXKeyState;

	bool currentJKeyState = (GetAsyncKeyState('J') & 0x8000);
	if (currentJKeyState && !m_prevJKey)
	{
		m_sceneTimer -= 600;
		if (m_sceneTimer < 0) m_sceneTimer = 0;

		// 敵とUIの時間を戻す
		if (m_enemyManager) m_enemyManager->AddTime(-600);
		if (m_ui) m_ui->AddTime(-600);

		// ★ 画面上の敵や弾をリセット（プレイヤー以外を削除）
		auto it = m_objList.begin();
		while (it != m_objList.end())
		{
			// Playerで「ない」場合はリストから消去
			if (!std::dynamic_pointer_cast<Player>(*it)) {
				it = m_objList.erase(it);
			}
			else {
				++it;
			}
		}
	}
	m_prevJKey = currentJKeyState;


	// ▼ Lキーで10秒先送り (600フレーム)
	bool currentLKeyState = (GetAsyncKeyState('L') & 0x8000);
	if (currentLKeyState && !m_prevLKey)
	{
		m_sceneTimer += 600;

		// 敵とUIの時間を進める
		if (m_enemyManager) m_enemyManager->AddTime(600);
		if (m_ui) m_ui->AddTime(600);

		// ★ 画面上の敵や弾をリセット（プレイヤー以外を削除）
		auto it = m_objList.begin();
		while (it != m_objList.end())
		{
			// Playerで「ない」場合はリストから消去
			if (!std::dynamic_pointer_cast<Player>(*it)) {
				it = m_objList.erase(it);
			}
			else {
				++it;
			}
		}
	}
	m_prevLKey = currentLKeyState;

	// ---  UIへのHP反映と回復実行 ---
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
	if (m_enemyManager)
	{
		m_enemyManager->Update(m_objList);
	}

	// --- 2. 不要なオブジェクトの削除 (erase-removeイディオム) ---
	// 生存フラグが false のものを一括で削除
	auto it = m_objList.begin();
	while (it != m_objList.end())
	{
		if (!(*it)->IsAlive())
		{
			it = m_objList.erase(it); // リストから完全に消去
		}
		else
		{
			++it;
		}
	}
}

void GameScene::Init()
{
	// 1. ステージ（一番奥）
	m_stage = std::make_shared<Stage>();

	// 2. 当たり判定
	m_hitChecker = std::make_unique<Hit>();

	// 3. プレイヤー
	auto player = std::make_shared<Player>();
	m_objList.push_back(player);

	// 2. UI生成と連携
	m_ui = std::make_shared<UI>();
	m_ui->SetPlayer(player); // UIにプレイヤーを教える

	m_enemyManager = std::make_unique<EnemyManager>();
	m_enemyManager->LoadTimeline("Textures/TextDate/SpawnData.txt");
}

void GameScene::Release()
{
	m_objList.clear();
}