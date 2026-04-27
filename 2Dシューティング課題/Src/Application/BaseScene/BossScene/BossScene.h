#pragma once

#include "../BaseScene.h"

class Player;

class BossScene :public BaseScene
{
public:

	BossScene() { Init(); }
	~BossScene() { Release(); }

	void Update()override;
	void Draw()override;

	std::shared_ptr<Player> m_player;

private:

	void Init()override;
	void Release()override;
};

