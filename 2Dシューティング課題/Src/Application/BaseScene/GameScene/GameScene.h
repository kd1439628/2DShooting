#pragma once

#include "../BaseScene.h"

class Player;

class GameScene :public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	std::shared_ptr<Player> m_player;

private:



};

