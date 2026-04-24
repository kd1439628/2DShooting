#pragma once

#include "../BaseScene.h"

class Player;

class GameScene :public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() { Release(); }

	void Update()override;
	void Draw()override;

	std::shared_ptr<Player> m_player;

private:

	void Init()override;
	void Release()override;

};

