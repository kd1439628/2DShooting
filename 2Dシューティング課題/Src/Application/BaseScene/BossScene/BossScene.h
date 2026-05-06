#pragma once

#include "../BaseScene.h"

class BaseObject;

class BossScene :public BaseScene
{
public:

	BossScene() { Init(); }
	~BossScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

	std::vector<std::shared_ptr<BaseObject>> m_objList;

};

