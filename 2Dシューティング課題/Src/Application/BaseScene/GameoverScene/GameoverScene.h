#pragma once

#include "../BaseScene.h"

class GameoverScene :public BaseScene
{
public:

	GameoverScene() { Init(); }
	~GameoverScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

};

