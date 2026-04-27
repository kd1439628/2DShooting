#pragma once

#include "../BaseScene.h"

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

	std::vector<std::shared_ptr<BaseObject>> m_objList;

};

