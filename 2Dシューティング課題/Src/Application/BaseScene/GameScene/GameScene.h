#pragma once

#include "../BaseScene.h"
#include "../../Stage/Stage.h"
#include "../../BaseObject/Hit.h"
#include "../../UI/UI.h"

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

	int m_spawnTimer = 0;       // 次の敵が出るまでのカウントダウン
	int m_maxEnemyCount = 10;   // 画面内に同時に存在できる敵の上限

};

