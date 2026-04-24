#pragma once

#include "../BaseChara.h"

class Player :public BaseChara
{
public:

	Player() { Init(); }
	~Player() { Release(); }

	void Update();
	void Draw();

private:

	void Init();
	void Release();

};

