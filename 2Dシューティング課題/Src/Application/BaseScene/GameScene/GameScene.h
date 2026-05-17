#pragma once

#include "../BaseScene.h"
#include "../../Stage/GameStage/Stage.h"
#include "../../BaseObject/Hit.h"
#include "../../UI/UI.h"
#include "../../BaseObject/Enemies/EnemyManager.h"

class BaseObject;

class GameScene :public BaseScene
{
public:

	GameScene() {}
	~GameScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

	// 追加：ステージ
	std::shared_ptr<Stage> m_stage = nullptr;
	std::vector<std::shared_ptr<BaseObject>> m_objList;
	std::unique_ptr<Hit> m_hitChecker = std::make_unique<Hit>();
	std::shared_ptr<UI> m_ui = nullptr;

	int m_gameoverTimer = 60; // ゲームオーバー画面に行くまでの猶予

	std::unique_ptr<EnemyManager> m_enemyManager = nullptr;
	int m_sceneTimer = 0;

	bool m_prevJKey = false;
	bool m_prevLKey = false;
};

