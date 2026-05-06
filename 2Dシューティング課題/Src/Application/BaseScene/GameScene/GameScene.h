#pragma once

#include "../BaseScene.h"
#include "../../Stage/Stage.h"

class BaseObject;

class GameScene :public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

	// 追加：ステージ
	std::shared_ptr<Stage> m_stage = nullptr;
	std::vector<std::shared_ptr<BaseObject>> m_objList;

};

